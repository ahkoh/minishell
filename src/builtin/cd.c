/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 19:03:23 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"

bool	cd(char **argv, t_prompt *prompt, int *exit_status)
{
	(void)prompt;
	if (ft_strcmp(argv[0], "cd") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		if (argv[1] && chdir(argv[1]) == -1)
		{
			*exit_status = EXIT_FAILURE;
			ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
		}
		else
		{
			*exit_status = 2;
			ft_putendl_fd("minishell: cd: require a relative or absolute path",
				STDERR_FILENO);
		}
		return (true);
	}
	return (false);
}
