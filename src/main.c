/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/15 17:10:20 by skoh             ###   ########.fr       */
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

static char	*get_prompt(t_prompt *prompt)
{
	char	*cwd;

	if (prompt->debug)
	{
		cwd = getcwd(NULL, 0);
		printf("[%d]%s", prompt->e_status, cwd);
		free(cwd);
	}
	if (prompt->e_status)
		return ("\033[41m$\033[m ");
	return ("\033[44m$\033[m ");
}

// static char *freadline(void *a){(void)a;return ft_strdup("cat<<1|nl");}
static int	repl(char **env)
{
	t_prompt	prompt;

	prompt = (t_prompt){.env = init_env(env), .e_status = EXIT_SUCCESS};
	while (true)
	{
		signal(SIGINT, reprompt);
		prompt.full_cmds = readline(get_prompt(&prompt));
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
			free_cmds(&prompt.cmds, prompt.total_cmd);
		}
		free(prompt.full_cmds);
	}
	printf("exit\n");
	return (rl_clear_history(), ft_split_free(&prompt.env), prompt.e_status);
}

/* Bash returns the exit status of the last command executed */
/* or exits with a non-zero value when a syntax error occurs */
int	main(int argc, char **argv, char **env)
{
	if (argc > 1 && argv)
		return (ft_putendl_fd("Error: No parameter expected", 2), EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	return (repl(env));
}
