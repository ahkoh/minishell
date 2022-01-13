/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:41:15 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 18:36:37 by skoh             ###   ########.fr       */
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
	bool	debug;
}			t_prompt;

//get_cmd
char	**init_env(char **envp);
void	get_cmds(t_cmd **cmd, t_prompt *prompt);
void	free_cmds(t_cmd **cmd, int total_cmd);
//utils
bool	ft_isempty(char *line);
void	ft_split_free(char ***tab);
//fd_helper
void	fd_close(int f1, int f2);
void	fd_swap(int *fd, int target);
void	fd_replace(int *fd_dest, int fd_src);
//builtin
bool	execute_builtins(char **argv, t_prompt *prompt, int *exit_status);
//builtin/*
bool	cd(char **argv, t_prompt *prompt, int *exit_status);
bool	echo(char **argv, t_prompt *prompt, int *exit_status);
bool	env(char **argv, t_prompt *prompt, int *exit_status);
bool	quit(char **argv, t_prompt *prompt, int *exit_status);
bool	export(char **argv, t_prompt *prompt, int *exit_status);
bool	pwd(char **argv, t_prompt *prompt, int *exit_status);
bool	unset(char **argv, t_prompt *prompt, int *exit_status);
bool	debug(char **argv, t_prompt *prompt, int *exit_status);
//pipex_utils
int		px_execfile(char **argv, char **env);
//heredoc
bool	handle_heredocs(t_cmd *cmd, int count);
//redirect
int		open_redirections(t_cmd *cmd);
//executor
int		execute_line(t_cmd *cmd, t_prompt *prompt);

#endif
