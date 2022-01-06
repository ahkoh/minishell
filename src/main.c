/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <skoh@student.42kl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/06 09:04:22 by Koh              ###   ########.kl       */
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

static void	reprompt(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static bool	is_empty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line++))
			return (false);
	}
	return (true);
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

	(void) argv;
	if (argc > 1)
		return (ft_putendl_fd("Error: No parameter expected", 2), 1);
	last_error = false;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, reprompt);
		line = readline(prompt(last_error));
		signal(SIGINT, SIG_IGN);
		if (line == NULL)
			break ;
		if (is_empty(line))
			continue ;
		last_error = ft_execute(line, env);
		add_history(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
