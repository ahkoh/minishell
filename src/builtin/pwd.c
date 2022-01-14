/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:23:39 by skoh              #+#    #+#             */
/*   Updated: 2022/01/14 09:26:26 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

int	pwd(char **argv, t_prompt *prompt)
{
	char	*s;

	(void)argv;
	(void)prompt;
	s = getcwd(NULL, 0);
	printf("%s\n", s);
	free(s);
	return (EXIT_SUCCESS);
}
