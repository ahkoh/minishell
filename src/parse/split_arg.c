/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:56:17 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 22:57:34 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* init subsplit calling get_total_split and malloc_arg */
static void	init_subsplit(t_cmd **cmd, int a, char *s, t_split_space_var *var)
{
	var->total_split = get_total_split(s);
	malloc_arg(cmd, a, var->total_split, s);
	var->x = 0;
	var->y = 0;
	var->is_opened = false;
	var->is_operator = false;
}

/* hoes through the cmd and insert the arg into the malloced arg */
static void	insert_arg(t_cmd **cmd, int a, char *s, t_split_space_var *var)
{
	var->i = 0;
	while (s[var->y] != '\0' && (!(ft_isspace(s[var->y]))
			|| var->is_opened == true))
	{
		if (check_operator(s[var->y], var,
				&((*cmd)[a].is_operator[var->x + 1])))
			break ;
		else if (check_quote_status(s[var->y], var) == -1)
			;
		else
		{
			(*cmd)[a].arg[var->x][var->i] = s[var->y];
			var->i++;
		}
		var->y++;
	}
	(*cmd)[a].arg[var->x][var->i] = '\0';
}

/* goes throught the cmd and split and insert the cmd into individual arg*/
static void	ft_subsplit(t_cmd **cmd, int a, char *s, bool debug)
{
	t_split_space_var	var;

	init_subsplit(cmd, a, s, &var);
	while (var.x < var.total_split && s[var.y] && (*cmd)[a].arg[var.x])
	{
		while (s[var.y] != '\0' && ft_isspace(s[var.y]))
		{
			var.y++;
			var.is_operator = false;
		}
		check_operator(s[var.y], &var, &((*cmd)[a].is_operator[var.x]));
		insert_arg(cmd, a, s, &var);
		if (debug)
			printf("[%d] %s\n", (*cmd)[a].is_operator[var.x],
				(*cmd)[a].arg[var.x]);
		var.x++;
	}
}

/* goes through each cmd and split them into individual arg */
void	split_arg(t_cmd **cmd, t_prompt *prompt)
{
	int					a;

	a = 0;
	while (a < prompt->total_cmd)
	{
		if (prompt->debug)
			printf("cmd %d\n", a);
		ft_subsplit(cmd, a, (*cmd)[a].cmd, prompt->debug);
		if (prompt->debug)
			printf("\n");
		a++;
	}
}
