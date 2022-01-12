/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 03:45:17 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

// todo free(everything)?
static bool	quit(char **argv, int *exit_status)
{
	if (ft_strcmp(argv[0], "exit") == 0)
	{
		printf("exit\n");
		*exit_status = EXIT_SUCCESS;
		if (argv[1])
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: no argument expected\n");
			*exit_status = 1;
		}
		exit(*exit_status);
		return (true);
	}
	return (false);
}

static bool	cd(char **argv, int *exit_status)
{
	if (ft_strcmp(argv[0], "cd") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		if (argv[1] && chdir(argv[1]) == -1)
		{
			*exit_status = EXIT_FAILURE;
			perror(argv[0]);
		}
		return (true);
	}
	return (false);
}

static bool	pwd(char **argv, int *exit_status)
{
	char	*s;

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

static bool	echo(char **argv, int *exit_status)
{
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

// run built-in if matched and no-cmd
// exit_status = 0/1/2 => success/failure/syntax-error
// return true if is a built-in command, otherwise false
bool	execute_builtins(char **argv, t_prompt *prompt, int *exit_status)
{
	*exit_status = EXIT_SUCCESS;
	return (
		*argv == NULL
		|| cd(argv, exit_status)
		|| pwd(argv, exit_status)
		|| echo(argv, exit_status)
		|| quit(argv, exit_status)
		|| execute_environments(argv, prompt, exit_status));
}
