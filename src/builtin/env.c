/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:39:06 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 09:25:44 by skoh             ###   ########.fr       */
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

int	env(char **argv, t_prompt *prompt)
{
	(void)argv;
	mini_env(prompt);
	return (EXIT_SUCCESS);
}
