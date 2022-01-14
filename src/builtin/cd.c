/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/14 09:23:14 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include "libft.h"
#include "minishell.h"

int	cd(char **argv, t_prompt *prompt)
{
	(void)prompt;
	if (argv[1] == NULL)
	{
		ft_putendl_fd("minishell: cd: require a relative or absolute path",
			STDERR_FILENO);
		return (2);
	}
	else if (chdir(argv[1]) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
}
