/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 00:47:22 by skoh              #+#    #+#             */
/*   Updated: 2022/01/10 01:25:59 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	px_heredoc(char *delimiter, int fd)
{
	char		*line;
	const char	*prompt = "> ";

	ft_putstr_fd(prompt, STDOUT_FILENO);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
		ft_putstr_fd(prompt, STDOUT_FILENO);
	}
	free(line);
	close(fd);
}

// todo check error format eg ("minishell: %s: %s\n", strerror(errno), filename)
static void	openfile(t_cmd *cmd, char *operator, char *fp)
{
	int	fd[2];

	errno = 0;
	if (ft_strcmp("<<", operator) == 0)
	{
		pipe(fd);
		cmd->infile = fd[0];
		px_heredoc(fp, fd[1]);
	}
	else if (ft_strcmp("<", operator) == 0)
		cmd->infile = open(fp, O_RDONLY);
	else if (ft_strcmp(">>", operator) == 0)
		cmd->outfile = open(fp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (ft_strcmp(">", operator) == 0)
		cmd->outfile = open(fp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (errno)
		perror("minishell");
}

/* reset in, out fd then open fd based on argv[] & is_operator[] */
/* remove & free() redirect operator & filename from argv[], for execve() */
void	redirect(t_cmd *cmd, int count)
{
	int		arg_i;
	char	*operator;
	char	*fp;
	int		i;

	while (count && count--)
	{
		arg_i = (cmd->infile = (cmd->outfile = 0));
		i = -1;
		while (cmd->arg[arg_i] && ++i > -1)
		{
			if (!cmd->is_operator[i] && ++arg_i)
				continue ;
			operator = ft_shift(cmd->arg + arg_i);
			if (!cmd->is_operator[i + 1])
			{
				fp = ft_shift(cmd->arg + arg_i);
				if (fp)
					openfile(cmd, operator, fp);
				free(fp);
			}
			free(operator);
		}
		cmd++;
	}
}
