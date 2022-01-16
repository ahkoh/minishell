/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:34:03 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/16 14:03:52 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_expand
{
	int	a;
	int	b;
	int	opened;
	int	quote;
}				t_expand;

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
		return (ft_strreplace(&((*cmd)[var.a].cmd), ft_itoa(prompt->e_status),
			2, var.b - 1));
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

int	add_quote(t_cmd **cmd, t_expand var)
{
	int	i;

	if (var.opened == -1)
	{
		ft_strreplace(&(*cmd)[var.a].cmd, "'", 0, var.b);
		i = var.b + 2;
		while (ft_isalnum((*cmd)[var.a].cmd[i])
			|| (*cmd)[var.a].cmd[i] == '_')
			i++;
		ft_strreplace(&(*cmd)[var.a].cmd, "'", 0, i);
		return (1);
	}
	return (0);
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
			{
				var.b += add_quote(cmd, var);
				printf("%d\n", var.b);
				var.b += expand_env(cmd, prompt, var);
				if (var.opened == -1)
					var.b += 1;
				printf("%d\n", var.b);
			}
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
