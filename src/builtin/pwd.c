/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:23:39 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 16:20:35 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

bool	pwd(char **argv, t_prompt *prompt, int *exit_status)
{
	char	*s;

	(void)prompt;
	if (ft_strcmp(argv[0], "pwd") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		s = getcwd(NULL, 0);
		printf("%s\n", s);
		free(s);
		return (true);
	}
	return (false);
}
