/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/16 11:47:04 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// cleanup_heredocs() is called before quit()
int	quit(char **argv, t_prompt *prompt)
{
	(void)prompt;
	printf("exit\n");
	if (argv[1])
	{
		ft_putendl_fd("minishell: exit: no argument expected",
			STDERR_FILENO);
		cleanup(prompt);
		exit(EXIT_FAILURE);
	}
	cleanup(prompt);
	exit(EXIT_SUCCESS);
}
