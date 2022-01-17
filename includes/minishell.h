/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:41:15 by skoh              #+#    #+#             */
/*   Updated: 2022/01/17 10:37:05 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

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
	t_cmd	*cmds;
}			t_prompt;

typedef int	(*t_builtin_func)(char **argv, t_prompt *prompt);

typedef struct s_split_cmd_var
{
	int		a;
	int		b;
	int		size;
	int		start;
	int		opened;
	char	quote;
}				t_split_cmd_var;

typedef struct s_split_space_var
{
	int		x;
	int		y;
	int		i;
	int		total_split;
	bool	is_opened;
	bool	is_operator;
	char	quote_type;
}				t_split_space_var;

typedef struct s_expand
{
	int	a;
	int	b;
	int	opened;
	int	quote;
}				t_expand;

//parse
void	free_cmds(t_cmd **cmd, int total_cmd);
void	split_cmds(t_cmd **cmd, char *line);
int		count_total_cmd(char *line);
void	expand_cmd(t_cmd **cmd, t_prompt *prompt);
int		get_total_split(char *s);
void	malloc_arg(t_cmd **cmd, int a, int total_split, char *s);
int		split_arg(t_cmd **cmd, t_prompt *prompt);
int		is_quote(char c);
int		is_op(char c);
int		check_quote_status(char c, t_split_space_var *var);
int		check_operator(char c, t_split_space_var *var, bool *is_op);
int		mini_env(t_prompt *prompt);
int		mini_export(t_prompt *prompt, char **argv);
int		mini_unset(t_prompt *prompt, char **argv);
//get_cmd
char	**init_env(char **envp);
int		get_cmds(t_cmd **cmd, t_prompt *prompt);
//executor/utils
bool	ft_isempty(char *line);
void	ft_split_free(char ***tab);
//fd_helper
void	fd_dup_io(int *fin, int *fout, bool dup_io);
void	fd_close(int f1, int f2);
void	fd_replace(int *fd_dest, int fd_src);
//syntax
bool	check_syntax(t_cmd *cmd, int count);
//builin/builtin.c
bool	get_builtin_function(char *cmd, t_builtin_func *f);
//builtin/*
int		cd(char **argv, t_prompt *prompt);
int		echo(char **argv, t_prompt *prompt);
int		env(char **argv, t_prompt *prompt);
int		quit(char **argv, t_prompt *prompt);
int		export(char **argv, t_prompt *prompt);
int		pwd(char **argv, t_prompt *prompt);
int		unset(char **argv, t_prompt *prompt);
int		debug(char **argv, t_prompt *prompt);
//pipex_utils
int		px_execfile(char **argv, char **env);
//heredoc
bool	handle_heredocs(t_prompt *prompt, t_list **heredocs);
//redirect
int		open_redirections(t_cmd *cmd, t_list *heredocs);
//executor
int		execute_line(t_cmd *cmd, t_prompt *prompt);
//cleanup
void	cleanup(t_prompt *prompt);
void	cleanup_cmd(t_prompt *prompt);
void	cleanup_heredocs(t_list **heredocs);
void	cleanup_redirections(int fd1, int fd2);
#endif
