/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:39:28 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 10:41:25 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

/* check if the arg is valid
   if no display error and set exit status to 1
   if yes shift the env variable and free it */
void	find_and_unset(t_prompt *prompt, char *s)
{
	int	i;
	int	a;

	i = 0;
	while (prompt->env[i])
	{
		a = 0;
		while (s[a] && ft_isalnum(s[a]) && prompt->env[i][a] == s[a])
			a++;
		if (ft_isdigit(s[0]) || (!ft_isalnum(s[a])
				&& s[a] != '\0' && s[a] != '_'))
		{
			printf("unset: '%s': not a valid identifier\n", s);
			prompt->e_status = 1;
			break ;
		}
		if (s[a] == '\0' && prompt->env[i][a] == '=')
		{
			free(ft_shift(prompt->env + i));
			break ;
		}
		i++;
	}
}

/* goes through the arg and find and unset the env variable */
int	mini_unset(t_prompt *prompt, char **argv)
{
	int		a;

	a = 0;
	prompt->e_status = 0;
	while (argv[a] != NULL)
	{
		find_and_unset(prompt, argv[a]);
		a++;
	}
	return (prompt->e_status);
}

int	unset(char **argv, t_prompt *prompt)
{
	return (mini_unset(prompt, argv + 1));
}
