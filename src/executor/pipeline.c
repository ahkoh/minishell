/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/14 09:45:33 by skoh             ###   ########.fr       */
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

/* command is either built-in or executable file */
/* executable returns pid for waitpid() to get exit status */
/* built-in returns EXIT_SUCCESS/FAILURE/2(incorrect usage) as exit status */
/* minishell ignore ctrl+c, but forked cmd will react to ctrl+c */
static int	execute_redirect(t_cmd *cmd, t_prompt *prompt)
{
	int				pid;
	int				exit_status;
	t_builtin_func	func;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!open_redirections(cmd))
			exit_status = EXIT_FAILURE;
		else
		{
			fd_dup_io(&cmd->infile, &cmd->outfile, false);
			if (get_builtin_function(cmd->arg[0], &func))
				exit(func(cmd->arg, prompt));
			exit_status = px_execfile(cmd->arg, prompt->env);
		}
		exit(exit_status);
	}
	return (pid);
}

// todo: close pipe[0] in fork child
int	execute_pipeline(t_cmd *cmd, t_prompt *prompt)
{
	int		cnt;
	int		fi;
	int		p[2];
	int		last_pid;

	last_pid = EXIT_SUCCESS;
	fi = STDIN_FILENO;
	cnt = prompt->total_cmd;
	while (cnt && cnt--)
	{
		if (cnt)
			pipe(p);
		else
			p[1] = STDOUT_FILENO;
		if (cmd->infile)
			fd_close(fi, 0);
		else
			cmd->infile = fi;
		cmd->outfile = p[1];
		last_pid = execute_redirect(cmd, prompt);
		fd_close(fi, p[1]);
		fi = p[0];
		cmd++;
	}
	return (wait_exit_status(last_pid));
}

// todo single built-in run local, export can redirect!!
// return last command exit-status
int	execute_line(t_cmd *cmd, t_prompt *prompt)
{
	t_builtin_func	func;

	if (!check_syntax(cmd, prompt->total_cmd, &prompt->e_status))
		return (prompt->e_status);
	if (!handle_heredocs(cmd, prompt->total_cmd))
		return (EXIT_FAILURE);
	if (prompt->total_cmd == 1 && get_builtin_function(cmd->arg[0], &func))
	{
		if (!open_redirections(cmd))
			return (EXIT_FAILURE);
		fd_dup_io(&cmd->infile, &cmd->outfile, true);
		prompt->e_status = func(cmd->arg, prompt);
		fd_dup_io(&cmd->infile, &cmd->outfile, false);
		return (prompt->e_status);
	}
	return (execute_pipeline(cmd, prompt));
}
