/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 15:25:51 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

bool	echo(char **argv, t_prompt *prompt, int *exit_status)
{
	(void)prompt;
	if (ft_strcmp(*argv, "echo") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		while (*++argv)
		{
			printf("%s", *argv);
			if (argv[1])
				printf(" ");
		}
		printf("\n");
		return (true);
	}
	return (false);
}
