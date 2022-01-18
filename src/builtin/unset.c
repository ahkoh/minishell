/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:39:28 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/18 17:21:45 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

bool	check_env_identifier(char *s, bool has_equal)
{
	if (!(*s == '_' || ('A' <= *s && *s <= 'Z') || ('a' <= *s && *s <= 'z')))
		return (false);
	while (*s && (ft_isalnum(*s) || *s == '_'))
		s++;
	if (has_equal && *s == '=')
		return (true);
	return (*s == '\0');
}

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

	prompt->e_status = 0;
	a = -1;
	while (argv[++a] != NULL)
	{
		if (!check_env_identifier(argv[a], false))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv[a], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			prompt->e_status = 1;
			continue ;
		}
		find_and_unset(prompt, argv[a]);
	}
	return (prompt->e_status);
}

int	unset(char **argv, t_prompt *prompt)
{
	return (mini_unset(prompt, argv + 1));
}
