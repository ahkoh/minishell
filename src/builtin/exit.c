/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 15:22:27 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// todo free(everything)?
bool	quit(char **argv, t_prompt *prompt, int *exit_status)
{
	(void)prompt;
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		printf("exit\n");
		*exit_status = EXIT_SUCCESS;
		if (argv[1])
		{
			ft_putendl_fd("minishell: exit: no argument expected",
				STDERR_FILENO);
			*exit_status = 1;
		}
		exit(*exit_status);
		return (true);
	}
	return (false);
}
