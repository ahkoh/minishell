/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:52:56 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/09 11:31:41 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../libft/libft.h"

typedef struct s_cmd
{
	char *cmd;
	char **arg;
	int infile;
	int outfile;
	bool *is_operator;
}			t_cmd;

typedef struct s_prompt
{
	char *full_cmds;
	char **env;
	int e_status;
	int total_cmd;
}			t_prompt;

void ft_strreplace(char **cmd, char *replace, int size_search, int search_index)
{
	int b;
	int c;
	int d;
	char *new_str;

	new_str = malloc(sizeof(char) *
		(ft_strlen((*cmd)) - size_search + ft_strlen(replace) + 1));
	b = -1;
	c = -1;
	d = -1;
	while ((*cmd)[++b] != '\0')
	{
		if (b == search_index)
		{
			while (replace[++d] != '\0')
				new_str[++c] = replace[d];
			b += size_search;
		}
		new_str[++c] = (*cmd)[b];
	}
	new_str[++c] = '\0';
	free((*cmd));
	(*cmd) = new_str;
}

char *find_env(char *cmd, t_prompt *prompt, int len)
{
	int a;
	int b;

	a = 0;
	len--;
	while (prompt->env[a])
	{
		b = 0;
		while ((ft_isalnum(cmd[b]) || cmd[b] == '_') && b < len)
		{
			if (prompt->env[a][b] != cmd[b])
				break;
			b++;
		}
		if (b == len && prompt->env[a][b] == '=')
			return (&prompt->env[a][b + 1]);
		a++;
	}
	return (NULL);
}

void expand_env(t_cmd **cmd, t_prompt *prompt, int a, int b)
{
	int tmp;
	int env_len;
	char *replace;

	b++;
	// if ((*cmd)[a].cmd[b] == '$')
	// 	ft_strreplace(&((*cmd)[a].cmd), ft_itoa(getpid()), 2, b - 1);
	if ((*cmd)[a].cmd[b] == '?')
		ft_strreplace(&((*cmd)[a].cmd), ft_itoa(prompt->e_status), 2, b - 1);
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
			ft_strreplace(&((*cmd)[a].cmd), replace, env_len, tmp - 1);
		else if (replace == NULL && env_len > 1)
			ft_strreplace(&((*cmd)[a].cmd), "", env_len, tmp - 1);
	}
}

void expand_cmd(t_cmd **cmd, t_prompt *prompt)
{
	int a;
	int b;
	int opened;

	a = 0;
	while (a < prompt->total_cmd)
	{
		b = 0;
		opened = 1;
		while ((*cmd)[a].cmd[b] != '\0')
		{
			if ((*cmd)[a].cmd[b] == '$' && opened == 1)
				expand_env(cmd, prompt, a, b);
			if ((*cmd)[a].cmd[b] == '\'')
				opened *= -1;
			b++;
		}
		a++;
	}
}

// char	*ft_strndup(const char *s1, const int size)
// {
// 	char			*new;
// 	unsigned int	a;
// 	unsigned int	b;

// 	a = 0;
// 	b = 0;
// 	if (!(new = (char*)malloc(sizeof(char) * (size + 1))))
// 		return (NULL);
// 	while (s1[b] != '\0' && b < size)
// 	{
// 		new[b] = s1[b];
// 		b++;
// 	}
// 	new[b] = '\0';
// 	return (new);
// }

int count_total_cmd(char *line)
{
	int a;
	int opened;
	int total_cmd;
	char quote;

	a = 0;
	total_cmd = 1;
	opened = 1;
	while (line[a] != '\0')
	{
		if (line[a] == '|' && opened == 1)
			total_cmd++;
		if ((line[a] == '"' || line[a] == '\'') && opened == 1)
		{
			quote = line[a];
			opened *= -1;
		}
		else if (opened == -1 && line[a] == quote)
			opened *= -1;
		a++;
	}
	return (total_cmd);
}

typedef struct s_split_cmd_var
{
	int a;
	int b;
	int size;
	int start;
	int opened;
	char quote;
}		t_split_cmd_var;

void split_cmds(t_cmd **cmd, t_prompt *prompt, char *line)
{
	t_split_cmd_var var;

	var.a = -1;
	var.b = -1;
	var.size = 1;
	var.opened = 1;
	var.start = 0;
	while (line[++var.a] != '\0')
	{
		if ((line[var.a] == '|' && var.opened == 1))
		{
			(*cmd)[++var.b].cmd = ft_strndup(&line[var.start], var.size - 1);
			var.size = 0;
			var.start = var.a + 1;
		}
		else if ((line[var.a] == '"' || line[var.a] == '\'') && var.opened == 1)
		{
			var.quote = line[var.a];
			var.opened *= -1;
		}
		else if (var.opened == -1 && line[var.a] == var.quote)
			var.opened *= -1;
		var.size++;
	}
	(*cmd)[++var.b].cmd = ft_strndup(&line[var.start], var.size);
}

int is_whitespace(char c)
{
	int a;
	char *whitespace;

	a = 0;
	whitespace = " \t\n\v\f\r";
	while (whitespace[a] != '\0')
	{
		if (whitespace[a] == c)
			return (1);
		a++;
	}
	return (0);
}

typedef struct s_split_space_var
{
	int		x;
	int		y;
	int		i;
	int		total_split;
	bool	is_opened;
	bool	is_operator;
	char	quote_type;
}		t_split_space_var;

int is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int is_operator(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int check_quote_status(char c, t_split_space_var *var)
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

int get_total_split(char *s)
{
	t_split_space_var var;

	var.i = 0;
	var.total_split = 0;
	var.is_opened = false;
	while (s[var.i] != '\0' && is_whitespace(s[var.i]))
		var.i++;
	if (var.i == 0)
	{
		check_quote_status(s[var.i], &var);
		var.i++;
		var.total_split++;
	}
	while (s[var.i])
	{
		if ((is_whitespace(s[var.i - 1]) || is_operator(s[var.i - 1]))
			&& !is_whitespace(s[var.i]) && !is_operator(s[var.i]) && var.is_opened == false)
			var.total_split++;
		else if (is_operator(s[var.i]) && !is_operator(s[var.i - 1]) && var.is_opened == false)
			var.total_split++;
		check_quote_status(s[var.i], &var);
		var.i++;
	}
	return (var.total_split);
}

int check_operator(char c, t_split_space_var *var, bool *is_op)
{
	if (is_operator(c) && var->is_opened == false && var->is_operator == false)
	{
		var->is_operator = true;
		*is_op = true;
		return (1);
	}
	if (var->is_operator == true && !is_operator(c))
	{
		var->is_operator = false;
		return (1);
	}
	return (0);
}

void init_malloc_arg_var(t_split_space_var *var, t_cmd ** cmd, int total_split, int a)
{
	int i;

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

void malloc_arg(t_cmd **cmd, int a, int total_split, char *s)
{
	t_split_space_var var;

	init_malloc_arg_var(&var, cmd, total_split, a);
	while (var.x < total_split && s[var.y] != '\0')
	{
		var.i = 0;
		while (s[var.y] != '\0' && is_whitespace(s[var.y]))
		{
			var.y++;
			var.is_operator = false;
		}
		check_operator(s[var.y], &var, &((*cmd)[a].is_operator[var.x]));
		while (!(is_whitespace(s[var.y])) && s[var.y] != '\0' || var.is_opened == true)
		{
			if (check_operator(s[var.y], &var, &((*cmd)[a].is_operator[var.x + 1])))
				break;
			var.i += check_quote_status(s[var.y], &var);
			var.i++;
			var.y++;
		}
		(*cmd)[a].arg[var.x] = malloc(sizeof(char) * (var.i + 1));
		var.x++;
	}
}

void init_subsplit(t_cmd **cmd, int a, char *s, t_split_space_var *var)
{
	var->total_split = get_total_split(s);
	malloc_arg(cmd, a, var->total_split, s);
	var->x = 0;
	var->y = 0;
	var->is_opened = false;
	var->is_operator = false;
}

void ft_subsplit(t_cmd **cmd, int a, char *s)
{
	t_split_space_var var;

	init_subsplit(cmd, a, s, &var);
	while (var.x < var.total_split && s[var.y] && (*cmd)[a].arg[var.x])
	{
		var.i = -1;
		while (s[var.y] != '\0' && is_whitespace(s[var.y]))
		{
			var.y++;
			var.is_operator = false;
		}
		check_operator(s[var.y], &var, &((*cmd)[a].is_operator[var.x]));
		while (!(is_whitespace(s[var.y])) && s[var.y] != '\0' || var.is_opened == true)
		{
			if (check_quote_status(s[var.y], &var) == -1)
				;
			else if (check_operator(s[var.y], &var, &((*cmd)[a].is_operator[var.x + 1])))
				break;
			else
				(*cmd)[a].arg[var.x][++var.i] = s[var.y];
			var.y++;
		}
		(*cmd)[a].arg[var.x][++var.i] = '\0';
		printf("[%d] %s\n", (*cmd)[a].is_operator[var.x], (*cmd)[a].arg[var.x]);
		var.x++;
	}
}

void split_arg(t_cmd **cmd, t_prompt *prompt)
{
	int a;

	a = 0;
	while (a < prompt->total_cmd)
	{
		printf("cmd %d\n", a);
		ft_subsplit(cmd, a, (*cmd)[a].cmd);
		printf("\n");
		a++;
	}
}


void get_cmds(t_cmd **cmd, t_prompt *prompt)
{
	prompt->total_cmd = count_total_cmd(prompt->full_cmds);
	*cmd = malloc(sizeof(t_cmd) * (prompt->total_cmd));
	split_cmds(cmd, prompt, prompt->full_cmds);
	expand_cmd(cmd, prompt);
	split_arg(cmd, prompt);
}

char **init_env(char **envp)
{
	int a;
	char **env;

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

int main2(int ac, char **av, char **envp)
{
	t_prompt prompt;
	t_cmd *cmd;

	prompt.env = init_env(envp);
	prompt.e_status = 0;
	while (1)
	{
		prompt.full_cmds = readline("Text: ");
		get_cmds(&cmd, &prompt);
		free(prompt.full_cmds);
	}
	return (0);
}


// < : redirection has to split out
// "" : can connect to front and back when not whitespace (seems to be fixed)
// add a bool to check if operator is in quote
// clean up the ft_split