/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:12:20 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 10:12:56 by skoh             ###   ########.fr       */
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

// read stdin and write into pipe for later read
// return read-fd to get the saved string
static void	open_heredoc(char *delimiter, int fd)
{
	char	*line;
	char	*prompt;

	prompt = ft_strjoin(delimiter, "> ");
	while (true)
	{
		line = readline(prompt);
		if (line == NULL || ft_strcmp(line, delimiter) == 0)
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	free(prompt);
}

// reset in&out fd then open pipe for << based on argv[] & is_operator[]
// remove << operator & delimiter from argv[], for execve()
// expect syntax validated eg >file (operator followed by word)
// return list of delimiter and pipe-writer-fd per heredoc
static t_list	*find_heredocs(t_cmd *cmd, int count)
{
	int		arg_idx;
	int		operator_idx;
	t_list	*list;
	int		p[2];

	list = NULL;
	while (count && count--)
	{
		arg_idx = (cmd->infile = (cmd->outfile = 0));
		operator_idx = -1;
		while (cmd->arg[arg_idx] && ++operator_idx > -1)
		{
			if (!cmd->is_operator[operator_idx] && ++arg_idx)
				continue ;
			if (ft_strcmp("<<", cmd->arg[arg_idx]) != 0 && ++arg_idx)
				continue ;
			free(ft_shift(cmd->arg + arg_idx));
			ft_lstadd_back(&list, ft_lstnew(ft_shift(cmd->arg + arg_idx)));
			pipe(p);
			set_fd(&cmd->infile, p[0]);
			ft_lstadd_back(&list, ft_lstnew((void *)(long)p[1]));
		}
		cmd++;
	}
	return (list);
}

static	void	process_heredoc(t_list *heredocs, int fork_pid)
{
	const bool	is_child = fork_pid == 0;
	t_list		*next;

	if (is_child)
		signal(SIGINT, SIG_DFL);
	while (heredocs)
	{
		next = heredocs->next->next;
		if (is_child)
			open_heredoc(heredocs->content, (long)heredocs->next->content);
		close((long)heredocs->next->content);
		free(heredocs->content);
		free(heredocs->next);
		free(heredocs);
		heredocs = next;
	}
	if (is_child)
		exit(EXIT_SUCCESS);
}

// read all heredocs, ctrl+c will remove all */
bool	handle_heredocs(t_cmd *cmd, int count)
{
	int		pid;
	t_list	*heredocs;
	int		status;

	heredocs = find_heredocs(cmd, count);
	if (heredocs == NULL)
		return (true);
	pid = fork();
	process_heredoc(heredocs, pid);
	waitpid(pid, &status, 0);
	if (status)
	{
		printf("\n");
		while (count && count--)
		{
			if (cmd->infile)
				close(cmd->infile);
			cmd++;
		}
	}
	return (status == 0);
}
