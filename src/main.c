/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/13 17:27:00 by skoh             ###   ########.fr       */
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

/* prompt with cwd and react to $? */
/* compare export PS1='[$?]$LOGNAME:$(pwd)> ' */
static char	*get_prompt(t_prompt *prompt)
{
	char	*cwd;

	if (prompt->debug)
	{
		cwd = getcwd(NULL, 0);
		printf("[%d]%s", prompt->e_status, cwd);
		free(cwd);
	}
	return ("$ ");
}

// static char	*freadline(void *a) {(void)a; return ft_strdup("cat >a >b>c");}
// todo undo ctrl+d auto-newline
static int	repl(char **env)
{
	t_prompt	prompt;
	t_cmd		*cmd;

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
			get_cmds(&cmd, &prompt);
			prompt.e_status = execute_line(cmd, &prompt);
			add_history(prompt.full_cmds);
			if (prompt.e_status == 130)
				printf("\n");
			free_cmds(&cmd, prompt.total_cmd);
		}
		free(prompt.full_cmds);
	}
	ft_split_free(&prompt.env);
	printf("exit\n");
	return (prompt.e_status);
}

/* Bash returns the exit status of the last command executed */
/* or exits with a non-zero value when a syntax error occurs */
int	main(int argc, char **argv, char **env)
{
	if (argc > 1 && argv)
		return (ft_putendl_fd("Error: No parameter expected", 2), EXIT_FAILURE);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	return (repl(env));
}
