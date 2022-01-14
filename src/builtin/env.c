/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:39:06 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 10:41:00 by zhliew           ###   ########.fr       */
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
	return (prompt->e_status);
}

int	env(char **argv, t_prompt *prompt)
{
	(void)argv;
	return (mini_env(prompt));
}
