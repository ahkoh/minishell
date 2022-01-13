/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 13:41:15 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 09:50:07 by skoh             ###   ########.fr       */
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

//get_cmd
char	**init_env(char **envp);
void	get_cmds(t_cmd **cmd, t_prompt *prompt);
void	free_cmds(t_cmd **cmd, int total_cmd);
//utils
void	*ft_shift(void *pointer_array);
int		ft_strcmp(const char *s1, const char *s2);
bool	ft_isempty(char *line);
//builtins
bool	execute_builtins(char **argv, t_prompt *prompt, int *exit_status);
//environment
bool	execute_environments(char **argv, t_prompt *prompt, int *exit_status);
//pipex_utils
int		px_execfile(char **argv, char **env);
//heredoc
bool	handle_heredocs(t_cmd *cmd, int count);
//redirect
int		open_redirections(t_cmd *cmd);
void	set_fd(int *cur_fd, int new_fd);
//executor
int		execute_line(t_cmd *cmd, t_prompt *prompt);

#endif
