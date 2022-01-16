/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 06:31:11 by skoh              #+#    #+#             */
/*   Updated: 2022/01/16 11:56:29 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	cleanup_redirections(int fd1, int fd2)
{
	if (fd1 < fd2)
		fd1 = fd2;
	while (fd1 > STDERR_FILENO)
		close(fd1--);
}

void	cleanup_cmd(t_prompt *prompt)
{
	free_cmds(&prompt->cmds, prompt->total_cmd);
	prompt->total_cmd = 0;
	free(prompt->full_cmds);
	prompt->full_cmds = NULL;
}

void	cleanup_heredocs(t_list **heredocs)
{
	t_list	*next;

	while (*heredocs)
	{
		next = (*heredocs)->next->next;
		close((long)(*heredocs)->next->content / 1000000l);
		close((long)(*heredocs)->next->content % 1000000l);
		free((*heredocs)->next);
		free(*heredocs);
		*heredocs = next;
	}
}

void	cleanup(t_prompt *prompt)
{
	cleanup_cmd(prompt);
	ft_split_free(&prompt->env);
	rl_clear_history();
}
