/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <skoh@student.42kl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/07 13:26:15 by Koh              ###   ########.kl       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "libft.h"
#include <signal.h>

int	px_execfile(char *command, char **env);

static int	cd(char *line)
{
	if (ft_strnstr(line, "cd ", ft_strlen(line)) == line)
	{
		if (chdir(line + 3))
		{
			perror(line);
			return (-1);
		}
		return (1);
	}
	return (0);
}

/* 0 success, otherwise wstatus/errno */
static int	execute(char *line, char **env, int fi, int fo)
{
	int	pid;
	int	ret;

	ret = cd(line);
	if (ret)
		return (ret == -1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(fi, STDIN_FILENO);
		dup2(fo, STDOUT_FILENO);
		ret = px_execfile(line, env);
		exit(ret);
	}
	if (fi != STDIN_FILENO)
		close(fi);
	if (fo != STDOUT_FILENO)
		close(fo);
	return (pid);
}

/* execute pipe separated cmds */
static int	execute_pipe(char *line, char **env)
{
	char	**cmds;
	int		i;
	int		fi;
	int		p[2];
	int		pid;

	i = 0;
	cmds = ft_split(line, '|');
	fi = STDIN_FILENO;
	while (cmds[i])
	{
		if (cmds[i + 1])
			pipe(p);
		else
			p[1] = STDOUT_FILENO;
		pid = execute(cmds[i], env, fi, p[1]);
		fi = p[0];
		i++;
	}
	ft_split_free(&cmds);
	return (pid);
}

static int	ft_waitpid(int pid)
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

/* execute semicolons separated lines */
int	ft_execute(char *line, char **env)
{
	int		ret;
	char	**cmds;
	int		i;
	int		last_pid;

	ret = EXIT_SUCCESS;
	cmds = ft_split(line, ';');
	i = -1;
	while (cmds[++i])
	{
		last_pid = execute_pipe(cmds[i], env);
		if (last_pid > 1)
			ret = ft_waitpid(last_pid);
		else
			ret = last_pid;
		while (wait(NULL) > 0)
			;
	}
	ft_split_free(&cmds);
	return (ret);
}
