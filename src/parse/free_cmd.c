/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:51:25 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 20:38:18 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* free the t_cmd structure */
void	free_cmds(t_cmd **cmd, int total_cmd)
{
	int	a;
	int	b;

	a = 0;
	while (a < total_cmd)
	{
		b = 0;
		while ((*cmd)[a].arg[b] != NULL)
		{
			free((*cmd)[a].arg[b]);
			b++;
		}
		free((*cmd)[a].arg);
		free((*cmd)[a].is_operator);
		free((*cmd)[a].cmd);
		a++;
	}
	free((*cmd));
	*cmd = NULL;
}
