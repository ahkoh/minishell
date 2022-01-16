/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 08:12:20 by skoh              #+#    #+#             */
/*   Updated: 2022/01/16 11:32:58 by skoh             ###   ########.fr       */
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
		arg_idx = -1;
		operator_idx = -1;
		while (cmd->arg[++arg_idx] && ++operator_idx > -1)
		{
			if ((!cmd->is_operator[operator_idx]
					|| ft_strcmp("<<", cmd->arg[arg_idx]) != 0))
				continue ;
			pipe(p);
			ft_lstadd_back(&list, ft_lstnew(cmd->arg[arg_idx + 1]));
			ft_lstadd_back(&list, ft_lstnew((void *)(p[1] * 1000000l + p[0])));
		}
		cmd++;
	}
	return (list);
}

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

// parent close writer, keep reader
// fork uses writers, close everything
// 1 heredocs = 2 nodes (delimiter & (pipe[1] * 1000000 + pipe[0]))
static	int	fork_heredocs(t_list *heredocs, t_prompt *prompt)
{
	int		pid;
	t_list	*walk;

	pid = fork();
	if (pid)
	{
		while (heredocs)
		{
			close((long)heredocs->next->content / 1000000l);
			heredocs = heredocs->next->next;
		}
		return (pid);
	}
	signal(SIGINT, SIG_DFL);
	walk = heredocs;
	while (walk)
	{
		open_heredoc(walk->content, (long)walk->next->content / 1000000l);
		walk = walk->next->next;
	}
	cleanup_heredocs(&heredocs);
	cleanup(prompt);
	exit(EXIT_SUCCESS);
}

// make pipes for all <<
// read all heredocs at once in a fork(), ctrl+c will cancel all and cleanup
// return true if no heredoc or all success
bool	handle_heredocs(t_prompt *prompt, t_list **heredocs)
{
	int		pid;
	int		status;

	*heredocs = find_heredocs(prompt->cmds, prompt->total_cmd);
	if (*heredocs == NULL)
		return (true);
	pid = fork_heredocs(*heredocs, prompt);
	waitpid(pid, &status, 0);
	if (status)
	{
		cleanup_heredocs(heredocs);
		printf("\n");
	}
	return (status == 0);
}
