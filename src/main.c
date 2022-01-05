/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <skoh@student.42kl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/05 10:49:15 by Koh              ###   ########.kl       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include <stdbool.h>

int	ft_execute(char *command, char **env);

/* setup signals, handle CtrlC, ignore Ctrl\ */
static void	handle_signals(int signum)
{
	if (signum != SIGINT)
	{
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	(void)"TODO: kill child process";
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* add_history if neither duplicate nor empty */
static void	new_history(char *line)
{
	static char	buf[512];
	const int	size = sizeof(buf);

	if (line && *line && ft_strncmp(buf, line, size))
	{
		add_history(line);
		ft_strlcpy(buf, line, size);
	}
}

/* prompt with cwd and react to $? */
static char	*prompt(int errno)
{
	static char	buf[512];
	const int	size = sizeof(buf);
	int			len;

	ft_strlcpy(buf, "minishell:", size);
	len = ft_strlen(buf);
	getcwd(buf + len, size - len);
	if (errno)
		ft_strlcat(buf, "! ", size);
	else
		ft_strlcat(buf, "> ", size);
	return (buf);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		last_error;

	(void) argc;
	(void) argv;
	(void) env;
	last_error = false;
	handle_signals(true);
	while (1)
	{
		line = readline(prompt(last_error));
		if (line == NULL)
			break ;
		last_error = ft_execute(line, env);
		new_history(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
