/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:47:22 by skoh              #+#    #+#             */
/*   Updated: 2022/01/15 20:32:48 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

// redirection setup after fork(), it can be overwritten by later redirection
// one failed redirection will stop the single command execution with errormsg

static int	get_heredoc(t_list *heredocs, void *addr)
{
	while (heredocs)
	{
		if (heredocs->content == addr)
			return ((long)heredocs->next->content % 1000000l);
		heredocs = heredocs->next->next;
	}
	return (STDIN_FILENO);
}

// close previous fd if any, then open file for r/w, keep the fd in struct cmd
// failed open() will close all fds and set to -1, so we know to skip execution
static void	openfile(t_cmd *cmd, char *operator, char *fp, t_list *heredocs)
{
	if (cmd->infile == -1)
		return ;
	errno = 0;
	if (ft_strcmp("<<", operator) == 0)
		fd_replace(&cmd->infile, get_heredoc(heredocs, fp));
	else if (ft_strcmp("<", operator) == 0)
		fd_replace(&cmd->infile, open(fp, O_RDONLY));
	else if (ft_strcmp(">>", operator) == 0)
		fd_replace(&cmd->outfile, open(fp, O_CREAT | O_WRONLY | O_APPEND,
				0644));
	else if (ft_strcmp(">", operator) == 0)
		fd_replace(&cmd->outfile, open(fp, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (errno)
	{
		fd_replace(&cmd->infile, -1);
		fd_replace(&cmd->outfile, -1);
		ft_putstr_fd("Minishell: ", STDERR_FILENO);
		ft_putstr_fd(fp, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
}

// process argv[] & is_operator[] to open redirect-fd accordingly
// redirect param will be removed from argv[] for execve(argv)
// expect cmd->arg pre-validated eg operator must followed by word
// return false when open redirect-fd failed, otherwise true
int	open_redirections(t_cmd *cmd, t_list *heredocs)
{
	int		arg_idx;
	int		operator_idx;
	char	*operator;
	char	*fp;

	arg_idx = 0;
	operator_idx = -1;
	while (cmd->arg[arg_idx])
	{
		++operator_idx;
		if (!cmd->is_operator[operator_idx] && ++arg_idx)
			continue ;
		operator = ft_shift(cmd->arg + arg_idx);
		if (!cmd->is_operator[operator_idx + 1] && ++operator_idx)
		{
			fp = ft_shift(cmd->arg + arg_idx);
			if (fp)
				openfile(cmd, operator, fp, heredocs);
			free(fp);
		}
		free(operator);
	}
	return (cmd->infile != -1);
}
