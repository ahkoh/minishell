/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/12 10:58:43 by skoh             ###   ########.fr       */
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
// todo consider buf 512 limit
static char	*get_prompt(int last_exit_status)
{
	static char	buf[512];
	const int	size = sizeof(buf);
	int			len;

	ft_strlcpy(buf, "minishell:", size);
	len = ft_strlen(buf);
	getcwd(buf + len, size - len);
	if (last_exit_status)
		ft_strlcat(buf, "! ", size);
	else
		ft_strlcat(buf, "> ", size);
	return (buf);
}

// static char	*freadline(void *a) {(void)a; return ft_strdup("cat<a>a");}
// todo undo ctrl+d auto-newline
static int	repl(char **env)
{
	t_prompt	prompt;
	t_cmd		*cmd;

	prompt = (t_prompt){.env = init_env(env), .e_status = EXIT_SUCCESS};
	while (true)
	{
		signal(SIGINT, reprompt);
		prompt.full_cmds = readline(get_prompt(prompt.e_status));
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
			printf("[$?=%d]", prompt.e_status);
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
