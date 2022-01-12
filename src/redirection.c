/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:47:22 by skoh              #+#    #+#             */
/*   Updated: 2022/01/12 11:40:04 by skoh             ###   ########.fr       */
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

// close existing fd before assigning to a new fd
static void	set_fd(int *cur_fd, int new_fd)
{
	if (*cur_fd > STDERR_FILENO)
		close(*cur_fd);
	*cur_fd = new_fd;
}

// close previous fd if any, then open file for r/w, keep the fd in struct cmd
// failed open() will close all fds and set to -1, so we know to skip execution
static void	openfile(t_cmd *cmd, char *operator, char *fp)
{
	if (cmd->infile == -1)
		return ;
	errno = 0;
	if (ft_strcmp("<", operator) == 0)
		set_fd(&cmd->infile, open(fp, O_RDONLY));
	else if (ft_strcmp(">>", operator) == 0)
		set_fd(&cmd->outfile, open(fp, O_CREAT | O_WRONLY | O_APPEND, 0644));
	else if (ft_strcmp(">", operator) == 0)
		set_fd(&cmd->outfile, open(fp, O_CREAT | O_WRONLY | O_TRUNC, 0644));
	if (errno)
	{
		set_fd(&cmd->infile, -1);
		set_fd(&cmd->outfile, -1);
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", fp, strerror(errno));
	}
}

// process argv[] & is_operator[] to open redirect-fd accordingly
// redirect param will be removed from argv[] for execve(argv)
// expect cmd->arg pre-validated eg operator must followed by word
// return false when open redirect-fd failed, otherwise true
int	open_redirections(t_cmd *cmd)
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
		fp = ft_shift(cmd->arg + arg_idx);
		openfile(cmd, operator, fp);
		free(fp);
		free(operator);
	}
	return (cmd->infile != -1);
}
