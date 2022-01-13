/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 18:36:20 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// run built-in if matched and no-cmd
// exit_status = 0/1/2 => success/failure/syntax-error
// return true if is a built-in command, otherwise false
bool	execute_builtins(char **argv, t_prompt *prompt, int *exit_status)
{
	return (
		*argv == NULL
		|| cd(argv, prompt, exit_status)
		|| debug(argv, prompt, exit_status)
		|| echo(argv, prompt, exit_status)
		|| env(argv, prompt, exit_status)
		|| export(argv, prompt, exit_status)
		|| pwd(argv, prompt, exit_status)
		|| unset(argv, prompt, exit_status)
		|| quit(argv, prompt, exit_status));
}

// bool	execute_builtins(char **argv, t_prompt *prompt, int *exit_status)
// {
// 	int			i;
// 	const void	*fp[] = {
// 		"cd", &cd,
// 		"echo", &echo,
// 		"env", &env,
// 		"export", &export
// 	};

// 	*exit_status = EXIT_SUCCESS;
// 	i = -1;
// 	while (++i < (int)(sizeof(fp) / sizeof(*fp) / 2))
// 	{
// 		if (ft_strcmp(*argv, (char *)fp[i * 2]))
// 			continue ;
// 		((int (*)())(fp[i * 2 + 1]))(argv, prompt, exit_status);
// 		return (true);
// 	}
// 	return (false);
// }
