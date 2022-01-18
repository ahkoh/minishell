/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/18 15:59:28 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static int	check_option(char *s, char *options)
{
	int	r;

	r = 0;
	if (*s == '-')
	{
		while (*++s)
		{
			if (!ft_strchr(options, *s))
				return (0);
			r = r | 2 << (*s - 'a' + 1);
		}
	}
	return (r);
}

// use write() because printf(without_newline) may not flush to redirection
int	echo(char **argv, t_prompt *prompt)
{
	int	options;

	(void)prompt;
	options = 0;
	while (*++argv)
	{
		if (!check_option(*argv, "n"))
			break ;
		options = check_option(*argv, "n");
	}
	while (*argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		if (argv[1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		argv++;
	}
	if (!options)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
