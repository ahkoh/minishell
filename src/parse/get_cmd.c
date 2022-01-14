/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:52:56 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 11:58:31 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* get the input line and split it into individual command if pipe(|) exist
   then split the individual command to individual argv
   check if there is pipe (|) and no command, if yes display error*/
int	get_cmds(t_cmd **cmd, t_prompt *prompt)
{
	int	a;

	prompt->total_cmd = count_total_cmd(prompt->full_cmds);
	*cmd = malloc(sizeof(t_cmd) * (prompt->total_cmd));
	split_cmds(cmd, prompt->full_cmds);
	expand_cmd(cmd, prompt);
	if (split_arg(cmd, prompt))
	{
		prompt->e_status = 2;
		return (0);
	}
	a = 0;
	while (a < prompt->total_cmd)
	{
		if (prompt->total_cmd > 1 && (*cmd)[a].arg[0] == NULL)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			prompt->e_status = 2;
			return (0);
		}
		a++;
	}
	return (1);
}

char	**init_env(char **envp)
{
	int		a;
	char	**env;

	env = malloc(sizeof(char *) * 1001);
	a = -1;
	while (++a < 1001)
		env[a] = NULL;
	a = 0;
	while (envp[a])
	{
		env[a] = ft_strdup(envp[a]);
		a++;
	}
	return (env);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_prompt	prompt;
// 	t_cmd		*cmd;

// 	prompt.env = init_env(envp);
// 	prompt.e_status = 0;
// 	while (1)
// 	{
// 		prompt.full_cmds = readline("Text: ");
// 		get_cmds(&cmd, &prompt);
// 		free_cmds(&cmd, prompt.total_cmd);
// 		free(prompt.full_cmds);
// 	}
// 	return (0);
// }