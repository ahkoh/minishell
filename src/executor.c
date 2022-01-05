/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <skoh@student.42kl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:16:17 by Koh               #+#    #+#             */
/*   Updated: 2022/01/05 11:14:03 by Koh              ###   ########.kl       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "libft.h"

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

static bool	is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line++))
			return (false);
	}

	return (true);
}

/* 0 success, otherwise wstatus/errno */
int	ft_execute(char *line, char **env)
{
	int	ret;
	int	pid;

	if (is_empty(line))
		return (0);
	ret = cd(line);
	if (ret)
		return (ret == -1);
	pid = fork();
	if (pid == 0)
		return (px_execfile(line, env));
	waitpid(pid, &ret, 0);
	return (ret);
}
