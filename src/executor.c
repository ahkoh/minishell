/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/10 01:36:56 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "minishell.h"

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
static int	execute_command(char **argv, char **env, int fi, int fo)
{
	int	pid;
	int	exit_status;

	if (execute_builtins(argv, env, &exit_status))
		return (exit_status);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(fi, STDIN_FILENO);
		dup2(fo, STDOUT_FILENO);
		close_fd(fi, fo);
		exit_status = px_execfile(argv, env);
		exit(exit_status);
	}
	close_fd(fi, fo);
	return (pid);
}

// todo: close pipe[0] in fork child
int	execute_pipeline(t_cmd *cmd, t_prompt *prompt)
{
	int		cnt;
	int		fi;
	int		p[2];
	int		last_pid;

	redirect(cmd, prompt->total_cmd);
	last_pid = EXIT_SUCCESS;
	fi = STDIN_FILENO;
	cnt = prompt->total_cmd;
	while (cnt && cnt--)
	{
		if (cnt)
			pipe(p);
		else
			p[1] = STDOUT_FILENO;
		if (!cmd->infile)
			cmd->infile = fi;
		if (!cmd->outfile)
			cmd->outfile = p[1];
		last_pid = execute_command(cmd->arg, prompt->env,
				cmd->infile, cmd->outfile);
		fi = p[0];
		cmd++;
	}
	return (wait_exit_status(last_pid));
}
