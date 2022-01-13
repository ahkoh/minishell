/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:50:21 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 20:34:48 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*check if the character is quote*/
int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

/*check if the character is operator('<' or '>')*/
int	is_op(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

/*if the character is quote, check if it has a opening,
  if not, set true and save character
  if yes and charcter same as saved, set opening to false*/
int	check_quote_status(char c, t_split_space_var *var)
{
	if (is_quote(c) && var->is_opened == false)
	{
		var->quote_type = c;
		var->is_opened = true;
		return (-1);
	}
	else if (var->is_opened == true && c == var->quote_type)
	{
		var->is_opened = false;
		return (-1);
	}
	return (0);
}

/*if the character is operator, check that it is not inside quotes,
  if is operator set operator to true and flag to true
  if not set operator to false*/
int	check_operator(char c, t_split_space_var *var, bool *is_operator)
{
	if (is_op(c) && var->is_opened == false && var->is_operator == false)
	{
		var->is_operator = true;
		*is_operator = true;
		return (1);
	}
	if (var->is_operator == true && !is_op(c))
	{
		var->is_operator = false;
		return (1);
	}
	return (0);
}
