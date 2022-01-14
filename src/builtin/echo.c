/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/14 09:24:28 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// use write() because printf(without_newline) may not flush to redirection
int	echo(char **argv, t_prompt *prompt)
{
	bool	has_option_n;

	(void)prompt;
	has_option_n = argv[1] && ft_strcmp(argv[1], "-n") == 0 && ++argv;
	while (*++argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		if (argv[1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!has_option_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
