/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:41:15 by skoh              #+#    #+#             */
/*   Updated: 2022/01/09 13:41:16 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	int		infile;
	int		outfile;
	bool	*is_operator;
}			t_cmd;

typedef struct s_prompt
{
	char	*full_cmds;
	char	**env;
	int		e_status;
	int		total_cmd;
}			t_prompt;

char	**init_env(char **envp);
void	get_cmds(t_cmd **cmd, t_prompt *prompt);

bool	execute_builtins(char **argv, char **env, int *exit_status);

int		px_execfile(char **argv, char **env);

int		execute_pipeline(t_cmd **cmd, t_prompt *prompt);

#endif
