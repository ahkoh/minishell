/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/13 03:00:33 by skoh             ###   ########.fr       */
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

/* helper to close 1 or 2 fd by open(), avoiding STDIN/OUT/ERR */
static	void	close_fd(int f1, int f2)
{
	if (f1 > STDERR_FILENO)
		close(f1);
	if (f2 > STDERR_FILENO)
		close(f2);
}

/* command is either built-in or executable file */
/* executable returns pid for waitpid() to get exit status */
/* built-in returns EXIT_SUCCESS/FAILURE/2(incorrect usage) as exit status */
/* minishell ignore ctrl+c, but forked cmd will react to ctrl+c */
static int	execute_redirect(t_cmd *cmd, t_prompt *prompt)
{
	int	pid;
	int	exit_status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!open_redirections(cmd))
			exit_status = EXIT_FAILURE;
		else
		{
			dup2(cmd->infile, STDIN_FILENO);
			dup2(cmd->outfile, STDOUT_FILENO);
			close_fd(cmd->infile, cmd->outfile);
			if (execute_builtins(cmd->arg, prompt, &exit_status))
				exit(exit_status);
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
			close_fd(fi, 0);
		else
			cmd->infile = fi;
		cmd->outfile = p[1];
		last_pid = execute_redirect(cmd, prompt);
		close_fd(fi, p[1]);
		fi = p[0];
		cmd++;
	}
	return (wait_exit_status(last_pid));
}

// todo single built-in run local, export can redirect!!
int	execute_line(t_cmd *cmd, t_prompt *prompt)
{
	const char	*builtins[] = {"cd", "exit", "unset", "export", NULL};
	int			i;

	if (!handle_heredocs(cmd, prompt->total_cmd))
		return (EXIT_FAILURE);
	if (prompt->total_cmd == 1)
	{
		i = -1;
		while (builtins[++i])
		{
			if (ft_strcmp(builtins[i], cmd->arg[0]) != 0)
				continue ;
			execute_builtins(cmd->arg, prompt, &prompt->e_status);
			return (prompt->e_status);
		}
	}
	return (execute_pipeline(cmd, prompt));
}
