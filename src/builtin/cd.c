/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/18 06:58:09 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"

static void	set_pwd(t_prompt *prompt, const char *dir)
{
	char		*param[3];
	const char	*oldpwd;

	param[1] = NULL;
	oldpwd = get_const_value_by_key(prompt->env, "PWD");
	if (!oldpwd)
		oldpwd = "";
	param[0] = ft_strjoin("OLDPWD=", oldpwd);
	mini_export(prompt, param);
	free(param[0]);
	if (*dir == '/')
		param[2] = combine_path("", dir);
	else if (oldpwd && *oldpwd)
		param[2] = combine_path(oldpwd, dir);
	else
		param[2] = getcwd(NULL, 0);
	param[0] = ft_strjoin("PWD=", param[2]);
	mini_export(prompt, param);
	free(param[0]);
	free(param[2]);
}

int	change_dir(t_prompt *prompt, const char *path)
{
	int	exit_status;

	if (*path)
		exit_status = chdir(path);
	else
		exit_status = EXIT_SUCCESS;
	if (exit_status == EXIT_SUCCESS)
		set_pwd(prompt, path);
	else
	{
		exit_status = EXIT_FAILURE;
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd((char *)path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (exit_status);
}

int	cd(char **argv, t_prompt *prompt)
{
	const char	*home;

	if (argv[1] == NULL)
	{
		home = get_const_value_by_key(prompt->env, "HOME");
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
		else if (*home == '\0')
		{
			return (EXIT_SUCCESS);
		}
		return (change_dir(prompt, home));
	}
	return (change_dir(prompt, argv[1]));
}
