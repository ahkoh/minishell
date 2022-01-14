/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:34:03 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 11:17:46 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
static int	expand_env(t_cmd **cmd, t_prompt *prompt, int a, int b)
{
	int		tmp;
	int		env_len;
	char	*replace;

	b++;
	if ((*cmd)[a].cmd[b] == '?')
		return (ft_strreplace(&((*cmd)[a].cmd), ft_itoa(prompt->e_status),
			2, b - 1));
	else
	{
		env_len = 1;
		tmp = b;
		while (ft_isalnum((*cmd)[a].cmd[b]) || (*cmd)[a].cmd[b] == '_')
		{
			env_len++;
			b++;
		}
		replace = find_env(&((*cmd)[a].cmd[tmp]), prompt, env_len);
		if (replace != NULL && env_len > 1)
			return (ft_strreplace(&((*cmd)[a].cmd), replace, env_len, tmp - 1));
		else if (replace == NULL && env_len > 1)
			return (ft_strreplace(&((*cmd)[a].cmd), "", env_len, tmp - 1));
	}
	return (0);
}

/* check the cmd for '$' character, if it is not in '''
   find and replace the cmd */
void	expand_cmd(t_cmd **cmd, t_prompt *prompt)
{
	int		a;
	int		b;
	char	quote;
	int		opened;

	a = -1;
	while (++a < prompt->total_cmd)
	{
		b = -1;
		opened = -1;
		while ((*cmd)[a].cmd[++b] != '\0')
		{
			if ((*cmd)[a].cmd[b] == '$' && (opened == -1
					|| (opened == 1 && quote == '"')))
				b += expand_env(cmd, prompt, a, b);
			else if (opened == -1 && ((*cmd)[a].cmd[b] == '\''
				|| (*cmd)[a].cmd[b] == '"' ))
			{
				quote = (*cmd)[a].cmd[b];
				opened *= -1;
			}
			else if (opened == 1 && (*cmd)[a].cmd[b] == quote)
				opened *= -1;
		}
	}
}


// if env has operator character it will expand it and mark it as a operator character instead of a character
// exp: PS1=42$>