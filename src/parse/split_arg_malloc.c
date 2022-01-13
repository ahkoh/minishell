/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_malloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:58:18 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 22:48:12 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* go through the string
   if it finds whitespace or operator add the total split */
int	get_total_split(char *s)
{
	t_split_space_var	var;

	var.i = 0;
	var.total_split = 0;
	var.is_opened = false;
	while (s[var.i] != '\0' && ft_isspace(s[var.i]))
		var.i++;
	if (var.i == 0 && s[var.i] != '\0')
	{
		check_quote_status(s[var.i], &var);
		var.i++;
		var.total_split++;
	}
	while (s[var.i])
	{
		if (!is_op(s[var.i]) && !ft_isspace(s[var.i]) && var.is_opened == false
			&& (ft_isspace(s[var.i - 1]) || is_op(s[var.i - 1])))
			var.total_split++;
		else if (is_op(s[var.i]) && !is_op(s[var.i - 1])
			&& var.is_opened == false)
			var.total_split++;
		check_quote_status(s[var.i], &var);
		var.i++;
	}
	return (var.total_split);
}

/* init the var for malloc_arg function,
   creates the total_split number of arg
   and the total_split number of bool (is_operator)
   to check if the arg is operator or not */
static void	init_malloc_arg_var(t_split_space_var *var,
	t_cmd **cmd, int total_split, int a)
{
	int	i;

	i = 0;
	var->x = 0;
	var->y = 0;
	var->is_operator = false;
	var->is_opened = false;
	(*cmd)[a].arg = malloc(sizeof(char *) * (total_split + 1));
	(*cmd)[a].arg[total_split] = NULL;
	(*cmd)[a].is_operator = malloc(sizeof(bool) * (total_split + 1));
	while (i < total_split)
	{
		(*cmd)[a].is_operator[i] = false;
		i++;
	}
}

/* malloc each individual arg size to the arg */
void	malloc_arg(t_cmd **cmd, int a, int total_split, char *s)
{
	t_split_space_var	var;

	init_malloc_arg_var(&var, cmd, total_split, a);
	while (var.x < total_split && s[var.y] != '\0')
	{
		var.i = 0;
		while (s[var.y] != '\0' && ft_isspace(s[var.y]))
		{
			var.y++;
			var.is_operator = false;
		}
		check_operator(s[var.y], &var, &((*cmd)[a].is_operator[var.x]));
		while (!(ft_isspace(s[var.y]))
			&& (s[var.y] != '\0' || var.is_opened == true))
		{
			if (check_operator(s[var.y], &var,
					&((*cmd)[a].is_operator[var.x + 1])))
				break ;
			var.i += check_quote_status(s[var.y], &var);
			var.i++;
			var.y++;
		}
		(*cmd)[a].arg[var.x] = malloc(sizeof(char) * (var.i + 1));
		var.x++;
	}
}
