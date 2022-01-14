/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/14 09:26:06 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// todo free(everything)?
int	quit(char **argv, t_prompt *prompt)
{
	(void)prompt;
	printf("exit\n");
	if (argv[1])
	{
		ft_putendl_fd("minishell: exit: no argument expected",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
