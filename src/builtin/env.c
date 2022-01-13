/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:39:06 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 22:40:42 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* display the programs env variable */
int	mini_env(t_prompt *prompt)
{
	int	a;

	a = 0;
	prompt->e_status = 0;
	while (prompt->env[a])
	{
		printf("%s\n", prompt->env[a]);
		a++;
	}
	return (1);
}

bool	env(char **argv, t_prompt *prompt, int *exit_status)
{
	if (ft_strcmp(*argv, "env") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		mini_env(prompt);
		return (true);
	}
	return (false);
}
