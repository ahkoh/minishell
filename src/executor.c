/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <skoh@student.42kl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/06 09:01:10 by Koh              ###   ########.kl       */
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
	int	ret;
	int	pid;

	ret = cd(line);
	if (ret)
		return (ret == -1);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(fi, 0);
		dup2(fo, 1);
		return (px_execfile(line, env));
	}
	if (fi != 0)
		close(fi);
	if (fo != 1)
		close(fo);
	waitpid(pid, &ret, 0);
	return (ret);
}

/* execute pipe separated cmds */
static int	execute_pipe(char *line, char **env)
{
	int		ret;
	char	**cmds;
	int		i;
	int		fi;
	int		p[2];

	i = 0;
	cmds = ft_split(line, '|');
	fi = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
			pipe(p);
		else
			p[1] = 1;
		ret = execute(cmds[i], env, fi, p[1]);
		fi = p[0];
		i++;
	}
	ft_split_free(&cmds);
	return (ret);
}

/* execute semicolons separated lines */
int	ft_execute(char *line, char **env)
{
	int		ret;
	char	**cmds;
	int		i;

	i = 0;
	cmds = ft_split(line, ';');
	while (cmds[i])
	{
		ret = execute_pipe(cmds[i], env);
		i++;
	}
	ft_split_free(&cmds);
	return (ret);
}
