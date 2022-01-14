/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/14 09:41:02 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

bool	get_builtin_function(char *cmd, t_builtin_func *f)
{
	int			i;
	const void	*ar[] = {
		"cd", &cd,
		"debug", &debug,
		"echo", &echo,
		"env", &env,
		"export", &export,
		"pwd", &pwd,
		"unset", &unset,
		"exit", &quit,
		NULL
	};

	i = 0;
	while (ar[i])
	{
		if (ft_strcmp(cmd, ar[i]) == 0)
		{
			*f = ar[i + 1];
			return (true);
		}
		i += 2;
	}
	return (false);
}
