/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 17:10:39 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

bool	debug(char **argv, t_prompt *prompt, int *exit_status)
{
	(void)prompt;
	if (ft_strcmp(argv[0], "debug") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		prompt->debug = !prompt->debug;
		printf("debug %d\n", prompt->debug);
		return (true);
	}
	return (false);
}
