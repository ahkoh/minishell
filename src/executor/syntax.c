/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:54:15 by skoh              #+#    #+#             */
/*   Updated: 2022/01/18 08:51:37 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"
#include "libft.h"

static void	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static bool	is_operator(char *s)
{
	return (ft_strcmp(s, "<") == 0
		|| ft_strcmp(s, "<<") == 0
		|| ft_strcmp(s, ">") == 0
		|| ft_strcmp(s, ">>") == 0
	);
}

bool	check_syntax(t_cmd *cmd, int count)
{
	int		idx;

	while (count && count--)
	{
		cmd->infile = STDIN_FILENO;
		cmd->outfile = STDOUT_FILENO;
		idx = -1;
		while (cmd->arg[++idx])
		{
			if (!cmd->is_operator[idx])
				continue ;
			if (cmd->arg[idx + 1] == NULL)
				return (print_syntax_error("newline"), false);
			else if (cmd->is_operator[idx + 1])
				return (print_syntax_error(cmd->arg[idx + 1]), false);
			else if (!is_operator(cmd->arg[idx]))
				return (print_syntax_error(cmd->arg[idx]), false);
		}
		cmd++;
	}
	return (true);
}
