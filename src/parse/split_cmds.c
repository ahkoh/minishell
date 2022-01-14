/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:46:29 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 10:41:53 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* count the total cmd based on how manay '|'(pipe) there is */
int	count_total_cmd(char *line)
{
	int		a;
	int		opened;
	int		total_cmd;
	char	quote;

	a = 0;
	total_cmd = 1;
	opened = 1;
	while (line[a] != '\0')
	{
		if (line[a] == '|' && opened == 1)
			total_cmd++;
		if ((line[a] == '"' || line[a] == '\'') && opened == 1)
		{
			quote = line[a];
			opened *= -1;
		}
		else if (opened == -1 && line[a] == quote)
			opened *= -1;
		a++;
	}
	return (total_cmd);
}

/* split the string into individual cmd based on '|'(pipe) */
void	split_cmds(t_cmd **cmd, char *line)
{
	t_split_cmd_var	var;

	var.a = (var.b = -1);
	var.size = 1;
	var.opened = 1;
	var.start = 0;
	while (line[++var.a] != '\0')
	{
		if ((line[var.a] == '|' && var.opened == 1))
		{
			(*cmd)[++var.b].cmd = ft_strndup(&line[var.start], var.size - 1);
			var.size = 0;
			var.start = var.a + 1;
		}
		else if ((line[var.a] == '"' || line[var.a] == '\'') && var.opened == 1)
		{
			var.quote = line[var.a];
			var.opened *= -1;
		}
		else if (var.opened == -1 && line[var.a] == var.quote)
			var.opened *= -1;
		var.size++;
	}
	(*cmd)[++var.b].cmd = ft_strndup(&line[var.start], var.size);
}
