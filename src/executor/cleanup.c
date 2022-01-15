/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 06:31:11 by skoh              #+#    #+#             */
/*   Updated: 2022/01/15 20:42:56 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// dbl-pointer to set NULL after free
static void	free_heredocs(t_list **heredocs)
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

void	cleanup_fd(int fd1, int fd2)
{
	if (fd1 < fd2)
		fd1 = fd2;
	while (fd1 > STDERR_FILENO)
		close(fd1--);
}

void	cleanup(t_prompt *prompt, t_list **heredocs)
{
	if (heredocs)
		free_heredocs(heredocs);
	if (prompt)
	{
		free_cmds(&prompt->cmds, prompt->total_cmd);
		prompt->total_cmd = 0;
		free(prompt->full_cmds);
		prompt->full_cmds = NULL;
		ft_split_free(&prompt->env);
	}
}
