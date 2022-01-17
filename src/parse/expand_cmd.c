/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:34:03 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/17 15:40:09 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	expand_exit_status(t_cmd **cmd, t_prompt *prompt, t_expand var)
{
	int		size;
	char	*s;

	s = ft_itoa(prompt->e_status);
	size = (ft_strreplace(&((*cmd)[var.a].cmd), s, 2, var.b - 1));
	free(s);
	return (size);
}

/* compare the cmd(can only be alpha or num or '_')
   and find if there is matching env variable
   if yes return the matching env variable (return the address after '=') */
static char	*find_env(char *cmd, t_prompt *prompt, int len)
{
	int	a;
	int	b;

	a = 0;
	len--;
	while (prompt->env[a])
	{
		b = 0;
		while ((ft_isalnum(cmd[b]) || cmd[b] == '_') && b < len)
		{
			if (prompt->env[a][b] != cmd[b])
				break ;
			b++;
		}
		if (b == len && prompt->env[a][b] == '=')
			return (&prompt->env[a][b + 1]);
		a++;
	}
	return (NULL);
}

/*if character is '?' replace with exit status
  else find if the cmd exist in the env variable
  if yes, replace the cmd to env variable
  if no, replace to empty*/
static int	expand_env(t_cmd **cmd, t_prompt *prompt, t_expand var)
{
	int		tmp;
	int		env_len;
	char	*rpl;

	var.b++;
	if ((*cmd)[var.a].cmd[var.b] == '?')
		return (expand_exit_status(cmd, prompt, var));
	else
	{
		env_len = 1;
		tmp = var.b;
		while (ft_isalnum((*cmd)[var.a].cmd[var.b])
			|| (*cmd)[var.a].cmd[var.b] == '_')
		{
			env_len++;
			var.b++;
		}
		rpl = find_env(&((*cmd)[var.a].cmd[tmp]), prompt, env_len);
		if (rpl != NULL && env_len > 1)
			return (ft_strreplace(&((*cmd)[var.a].cmd), rpl, env_len, tmp - 1));
		else if (rpl == NULL && env_len > 1)
			return (ft_strreplace(&((*cmd)[var.a].cmd), "", env_len, tmp - 1));
	}
	return (0);
}

static int	pre_and_expand_env(t_cmd **cmd, t_prompt *prompt, t_expand var)
{
	int	i;
	int	total_replace;

	total_replace = 0;
	if (var.opened == -1)
	{
		ft_strreplace(&(*cmd)[var.a].cmd, "'", 0, var.b);
		i = var.b + 2;
		if ((*cmd)[var.a].cmd[i] == '?')
			i++;
		else
		{
			while (ft_isalnum((*cmd)[var.a].cmd[i])
			|| (*cmd)[var.a].cmd[i] == '_')
				i++;
		}
		ft_strreplace(&(*cmd)[var.a].cmd, "'", 0, i);
		total_replace += 2;
		var.b++;
	}
	total_replace += expand_env(cmd, prompt, var);
	return (total_replace - 1);
}

/* check the cmd for '$' character, if it is not in '''
   find and replace the cmd */
void	expand_cmd(t_cmd **cmd, t_prompt *prompt)
{
	t_expand	var;

	var.a = -1;
	while (++var.a < prompt->total_cmd)
	{
		var.b = -1;
		var.opened = -1;
		while ((*cmd)[var.a].cmd[++var.b] != '\0')
		{
			if ((*cmd)[var.a].cmd[var.b] == '$' && (var.opened == -1
					|| (var.opened == 1 && var.quote == '"')))
				var.b += pre_and_expand_env(cmd, prompt, var);
			else if (var.opened == -1 && ((*cmd)[var.a].cmd[var.b] == '\''
				|| (*cmd)[var.a].cmd[var.b] == '"' ))
			{
				var.quote = (*cmd)[var.a].cmd[var.b];
				var.opened *= -1;
			}
			else if (var.opened == 1 && (*cmd)[var.a].cmd[var.b] == var.quote)
				var.opened *= -1;
			if ((*cmd)[var.a].cmd[var.b] == '\0')
				break ;
		}
	}
}
