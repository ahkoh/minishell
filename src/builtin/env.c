/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 03:07:29 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 16:20:59 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	mini_env(t_prompt *prompt);

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
