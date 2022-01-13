/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 16:02:18 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
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
			perror(argv[0]);
		}
		return (true);
	}
	return (false);
}
