/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/16 11:29:07 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static void	reprompt(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static char	*get_prompt(int exit_status, int is_debug)
{
	char	*cwd;

	if (is_debug)
	{
		cwd = getcwd(NULL, 0);
		printf("[%d]%s", exit_status, cwd);
		free(cwd);
	}
	if (exit_status)
		return ("\033[41m$\033[m ");
	return ("\033[44m$\033[m ");
}

static int	run_script(char *line, char **envp)
{
	t_prompt	prompt;
	char		**lines;
	int			i;

	ft_bzero(&prompt, sizeof(prompt));
	prompt.env = init_env(envp);
	lines = ft_split(line, ';');
	i = -1;
	while (lines[++i])
	{
		prompt.full_cmds = ft_strdup(lines[i]);
		if (get_cmds(&prompt.cmds, &prompt))
			prompt.e_status = execute_line(prompt.cmds, &prompt);
		cleanup_cmd(&prompt);
	}
	ft_split_free(&lines);
	cleanup(&prompt);
	return (prompt.e_status);
}

// static char *freadline(void *a){(void)a;return ft_strdup("cat<<1|nl");}
static int	minishell(char **envp)
{
	t_prompt	prompt;

	ft_bzero(&prompt, sizeof(prompt));
	prompt.env = init_env(envp);
	while (true)
	{
		signal(SIGINT, reprompt);
		prompt.full_cmds = readline(get_prompt(prompt.e_status, prompt.debug));
		signal(SIGINT, SIG_IGN);
		if (prompt.full_cmds == NULL)
			break ;
		if (!ft_isempty(prompt.full_cmds))
		{
			if (get_cmds(&prompt.cmds, &prompt))
				prompt.e_status = execute_line(prompt.cmds, &prompt);
			add_history(prompt.full_cmds);
			if (prompt.e_status == 130)
				printf("\n");
		}
		cleanup_cmd(&prompt);
	}
	printf("exit\n");
	cleanup(&prompt);
	return (prompt.e_status);
}

/* Bash returns the exit status of the last command executed */
/* or exits with a non-zero value when a syntax error occurs */
int	main(int argc, char **argv, char **envp)
{
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0)
		return (run_script(argv[2], envp));
	if (argc > 1 && argv)
	{
		ft_putendl_fd("Error: Wrong parameter(s)", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
	return (minishell(envp));
}
