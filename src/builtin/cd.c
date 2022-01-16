/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/17 02:10:50 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"

// must ended '/' to work
static char	*trim_path(char *c)
{
	const int	l = ft_strlen(c);
	int			i;
	int			j;

	i = 0;
	while (c[i])
	{
		if (ft_strncmp(c + i, "//", 2) == 0)
			ft_strlcpy(c + i, c + i + 1, l);
		else if (ft_strncmp(c + i, "/./", 3) == 0)
			ft_strlcpy(c + i, c + i + 2, l);
		else if (ft_strncmp(c + i, "/../", 4) == 0)
		{
			j = i + 3;
			while (i > 0 && i--)
				if (c[i] == '/')
					break ;
			ft_strlcpy(c + i, c + j, l);
		}
		else if (i && c[i] == '/' && c[i + 1] == '\0')
			c[i] = '\0';
		else
			i++;
	}
	return (c);
}

static char	*combine_path(char *a, char *b)
{
	char	*aa;
	char	*c;

	c = ft_strjoin(a, "/");
	aa = ft_strjoin(c, b);
	free(c);
	c = ft_strjoin(aa, "/");
	free(aa);
	return (trim_path(c));
}

static void	set_pwd(t_prompt *prompt, char *dir)
{
	char	*param[4];

	param[1] = NULL;
	if (*dir == '/')
		param[2] = combine_path("", dir);
	else
	{
		param[3] = get_value_by_key(prompt->env, "PWD");
		if (param[3] == NULL)
			return ;
		param[2] = combine_path(param[3], dir);
		free(param[3]);
	}
	param[0] = ft_strjoin("PWD=", param[2]);
	mini_export(prompt, param);
	free(param[0]);
	free(param[2]);
}

static int	change_dir(t_prompt *prompt, char *path)
{
	int	exit_status;

	exit_status = chdir(path);
	if (exit_status == EXIT_SUCCESS)
		set_pwd(prompt, path);
	else
	{
		exit_status = EXIT_FAILURE;
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (exit_status);
}

int	cd(char **argv, t_prompt *prompt)
{
	char	*home;
	int		exit_status;

	if (argv[1] == NULL)
	{
		home = get_value_by_key(prompt->env, "HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else if (*home == '\0')
		{
			free(home);
			return (EXIT_SUCCESS);
		}
		exit_status = change_dir(prompt, home);
		free(home);
		return (exit_status);
	}
	return (change_dir(prompt, argv[1]));
}
