/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/09 13:57:39 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "libft.h"
#include <signal.h>
#include "minishell.h"

static int	wait_exit_status(int pid)
{
	int	ret;
	int	status;

	ret = waitpid(pid, &status, 0);
	if (ret > 0)
	{
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ret = 128 + WTERMSIG(status);
		else
			ret = status;
	}
	return (ret);
}

/* command is either built-in or executable file */
/* executable returns pid for waitpid() to get exit status */
/* built-in returns EXIT_SUCCESS/FAILURE/2(incorrect usage) as exit status */
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
		exit_status = px_execfile(argv, env);
		exit(exit_status);
	}
	if (fi != STDIN_FILENO)
		close(fi);
	if (fo != STDOUT_FILENO)
		close(fo);
	return (pid);
}

int	execute_pipeline(t_cmd **cmd, t_prompt *prompt)
{
	int		i;
	int		fi;
	int		p[2];
	int		last_pid;
	int		exit_status;

	last_pid = EXIT_SUCCESS;
	fi = STDIN_FILENO;
	i = -1;
	while (++i < prompt->total_cmd)
	{
		if (i + 1 < prompt->total_cmd)
			pipe(p);
		else
			p[1] = STDOUT_FILENO;
		last_pid = execute_command((*cmd)[i].arg, prompt->env, fi, p[1]);
		fi = p[0];
	}
	if (last_pid > 2)
		exit_status = wait_exit_status(last_pid);
	else
		exit_status = last_pid;
	while (wait(NULL) > 0)
		;
	return (exit_status);
}

/* Execute a pipeline */
/* A pipeline is a sequence of one or more commands separated by | */
/* The return status of a pipeline is the exit status of the last command */
// static int	execute_pipeline(char *line, char **env)
// {
// 	char	**commands;
// 	int		i;
// 	int		fi;
// 	int		p[2];
// 	int		pid;

// 	i = 0;
// 	commands = ft_split(line, '|');
// 	fi = STDIN_FILENO;
// 	while (commands[i])
// 	{
// 		if (commands[i + 1])
// 			pipe(p);
// 		else
// 			p[1] = STDOUT_FILENO;
// 		pid = execute_command(commands[i], env, fi, p[1]);
// 		fi = p[0];
// 		i++;
// 	}
// 	ft_split_free(&commands);
// 	return (pid);
// }

/* execute semicolons separated lines */
// int	ft_execute(char *line, char **env)
// {
// 	int		exit_status;
// 	char	**pipelines;
// 	int		i;
// 	int		last_pid;

// 	exit_status = EXIT_SUCCESS;
// 	pipelines = ft_split(line, ';');
// 	i = -1;
// 	while (pipelines[++i])
// 	{
// 		last_pid = execute_pipeline(pipelines[i], env);
// 		if (last_pid > 2)
// 			exit_status = wait_exit_status(last_pid);
// 		else
// 			exit_status = last_pid;
// 		while (wait(NULL) > 0)
// 			;
// 	}
// 	ft_split_free(&pipelines);
// 	return (exit_status);
// }
