/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:12:20 by skoh              #+#    #+#             */
/*   Updated: 2022/01/12 11:10:44 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"
#include "libft.h"

// all heredoc run together (one by one) before redirection
// 1 ctrl+c will cancel & cleanup all heredocs and stop while execution

// flag: false to reset, true to cancel, 2 to enquire
static bool	is_heredoc_cancelled(int flag)
{
	static bool	is_cancel = false;

	if (flag < 2)
		is_cancel = flag;
	return (is_cancel);
}

// read stdin and write into pipe for later read
// return read-fd to get the saved string
static int	open_heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;
	char	*prompt;

	if (pipe(fd) == -1)
		return (-1);
	prompt = ft_strjoin(delimiter, "> ");
	while (true)
	{
		line = readline(prompt);
		if (is_heredoc_cancelled(2) || line == NULL
			|| ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	free(line);
	free(prompt);
	close(fd[1]);
	return (fd[0]);
}

// reset in, out fd then open fd based on argv[] & is_operator[]
// remove & free() redirect operator & filename from argv[], for execve()
// expect syntax validated eg >file (operator followed by word)
static void	find_heredocs(t_cmd *cmd, int count)
{
	int		arg_idx;
	int		operator_idx;
	char	*delimiter;

	while (count && count--)
	{
		arg_idx = (cmd->infile = (cmd->outfile = 0));
		operator_idx = -1;
		while (!is_heredoc_cancelled(2) && cmd->arg[arg_idx])
		{
			++operator_idx;
			if (!cmd->is_operator[operator_idx] && ++arg_idx)
				continue ;
			if (ft_strcmp("<<", cmd->arg[arg_idx]) != 0 && ++arg_idx)
				continue ;
			free(ft_shift(cmd->arg + arg_idx));
			delimiter = ft_shift(cmd->arg + arg_idx);
			if (cmd->infile > STDERR_FILENO)
				close(cmd->infile);
			cmd->infile = open_heredoc(delimiter);
			free(delimiter);
		}
		cmd++;
	}
}

// todo cancelling heredoc and execution quit and cleanup
// press-key message is a workaround to unblock readline() as we ending it
static void	canel_heredoc(int signum)
{
	extern int	rl_done;

	(void)signum;
	is_heredoc_cancelled(true);
	rl_done = 1;
	printf("\nExecution cancelled. Press any key to continue...\n");
}

// read all heredocs, ctrl+c will remove all */
int	handle_heredocs(t_cmd *cmd, int count)
{
	is_heredoc_cancelled(false);
	signal(SIGINT, canel_heredoc);
	find_heredocs(cmd, count);
	signal(SIGINT, SIG_IGN);
	if (is_heredoc_cancelled(2))
	{
		while (count && count--)
		{
			if (cmd->infile)
				close(cmd->infile);
			cmd++;
		}
	}
	return (is_heredoc_cancelled(2) == false);
}
