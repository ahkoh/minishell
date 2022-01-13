/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 18:55:42 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

bool	echo(char **argv, t_prompt *prompt, int *exit_status)
{
	bool	has_option_n;

	(void)prompt;
	if (ft_strcmp(*argv, "echo") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		has_option_n = argv[1] && ft_strcmp(argv[1], "-n") == 0 && ++argv;
		while (*++argv)
		{
			printf("%s", *argv);
			if (argv[1])
				printf(" ");
		}
		if (!has_option_n)
			printf("\n");
		return (true);
	}
	return (false);
}
