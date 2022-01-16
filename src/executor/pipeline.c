/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/16 14:53:08 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

// first step is heredoc, then need to consider single built-in changes env
// parent will setup & cleanup pipe() for pipelines with builtins & executables
// pipeline split into fork() where rediction(dup2) & execve() may success/fail

/* wait all children, get exit status from last_pid, support built-in exit */
/* last_pid can be built-in exit-code 0/1/2 */
static int	wait_exit_status(int last_pid)
{
	int	exit_status;
	int	status;
	int	pid;

	exit_status = last_pid;
	while (true)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
			else
				exit_status = status;
		}
	}
	return (exit_status);
}

// run built-in/external command in fork
// setup IO redirection and prepare for failures.
// siganls ignored by minishell will restore to default for fork
// free resources/fd since we exit()
static int	fork_command(t_cmd *cmd, t_prompt *prompt, t_list *heredocs)
{
	int				pid;
	int				exit_status;
	t_builtin_func	func;

	pid = fork();
	if (pid)
		return (pid);
	signal(SIGQUIT, SIG_DFL);
	if (!open_redirections(cmd, heredocs))
	{
		cleanup_heredocs(&heredocs);
		cleanup(prompt);
		exit(EXIT_FAILURE);
	}
	fd_dup_io(&cmd->infile, &cmd->outfile, false);
	cleanup_redirections(cmd->infile, cmd->outfile);
	cleanup_heredocs(&heredocs);
	if (get_builtin_function(cmd->arg[0], &func))
		exit_status = func(cmd->arg, prompt);
	else
		exit_status = px_execfile(cmd->arg, prompt->env);
	cleanup(prompt);
	exit(exit_status);
}

static int	execute_pipeline(t_cmd *cmd, t_prompt *prompt, t_list *heredocs)
{
	int		cnt;
	int		fi;
	int		p[2];
	int		last_pid;

	last_pid = EXIT_SUCCESS;
	fi = STDIN_FILENO;
	ft_bzero(p, sizeof(int) * 2);
	cnt = prompt->total_cmd;
	while (cnt && cnt--)
	{
		if (cnt)
			pipe(p);
		else
			p[1] = STDOUT_FILENO;
		cmd->infile = fi;
		cmd->outfile = p[1];
		last_pid = fork_command(cmd, prompt, heredocs);
		fd_close(0, cmd->outfile);
		fi = p[0];
		cmd++;
	}
	cleanup_redirections(fi, 0);
	cleanup_heredocs(&heredocs);
	return (wait_exit_status(last_pid));
}

// local builtin disable redirect-in/heredoc because readline() will read
int	execute_line(t_cmd *cmd, t_prompt *prompt)
{
	t_list			*heredocs;
	t_builtin_func	func;

	if (!check_syntax(cmd, prompt->total_cmd))
		return (258);
	if (!handle_heredocs(prompt, &heredocs))
		return (EXIT_FAILURE);
	if (prompt->total_cmd == 1 && get_builtin_function(cmd->arg[0], &func))
	{
		if (!open_redirections(cmd, heredocs))
			return (EXIT_FAILURE);
		fd_replace(&cmd->infile, STDIN_FILENO);
		fd_dup_io(&cmd->infile, &cmd->outfile, true);
		cleanup_heredocs(&heredocs);
		prompt->e_status = func(cmd->arg, prompt);
		fd_dup_io(&cmd->infile, &cmd->outfile, false);
		return (prompt->e_status);
	}
	return (execute_pipeline(cmd, prompt, heredocs));
}
