/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 03:07:29 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 03:07:30 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	mini_export(t_prompt *prompt, char **argv);
int	mini_env(t_prompt *prompt);
int	mini_unset(t_prompt *prompt, char **argv);

static bool	unset(char **argv, t_prompt *prompt, int *exit_status)
{
	if (ft_strcmp(*argv, "unset") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		mini_unset(prompt, argv + 1);
		return (true);
	}
	return (false);
}

static bool	export(char **argv, t_prompt *prompt, int *exit_status)
{
	if (ft_strcmp(*argv, "export") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		mini_export(prompt, argv + 1);
		return (true);
	}
	return (false);
}

static bool	env(char **argv, t_prompt *prompt, int *exit_status)
{
	if (ft_strcmp(*argv, "env") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		mini_env(prompt);
		return (true);
	}
	return (false);
}

bool	execute_environments(char **argv, t_prompt *prompt, int *exit_status)
{
	return (env(argv, prompt, exit_status)
		|| export(argv, prompt, exit_status)
		|| unset(argv, prompt, exit_status));
}
