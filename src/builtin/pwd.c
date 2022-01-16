/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:23:39 by skoh              #+#    #+#             */
/*   Updated: 2022/01/17 02:36:01 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"
#include <sys/stat.h>

// public function used by main.c
char	*get_pwd(t_prompt *prompt)
{
	char		*a;
	char		*b;
	struct stat	aa;
	struct stat	bb;

	a = getcwd(NULL, 0);
	stat(a, &aa);
	b = get_value_by_key(prompt->env, "PWD");
	if (b && stat(b, &bb) == 0)
	{
		if (aa.st_dev == bb.st_dev && aa.st_ino == bb.st_ino)
		{
			free(a);
			return (b);
		}
	}
	free(b);
	return (a);
}

int	pwd(char **argv, t_prompt *prompt)
{
	char	*s;

	(void)argv;
	s = get_pwd(prompt);
	printf("%s\n", s);
	free(s);
	return (EXIT_SUCCESS);
}
