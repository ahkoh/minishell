/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/10 01:37:17 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static bool	cd(char **argv, int *exit_status)
{
	if (ft_strcmp(argv[0], "cd") == 0)
	{
		if (!argv[1] || argv[2])
			*exit_status = 2;
		*exit_status = chdir(argv[1]);
		if (*exit_status)
			perror(argv[0]);
		return (true);
	}
	return (false);
}

/* exit_status = 0/1/2 => success/failure/syntax-error */
/* return true if is a built-in command, otherwise false */
bool	execute_builtins(char **argv, char **env, int *exit_status)
{
	(void)env;
	return (cd(argv, exit_status));
}
