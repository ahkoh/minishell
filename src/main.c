/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <skoh@student.42kl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/07 13:29:07 by Koh              ###   ########.kl       */
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
static char	*prompt(int last_exit_status)
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

int	main(int argc, char **argv, char **env)
{
	char	*line;
	int		last_exit_status;

	(void) argv;
	if (argc > 1)
		return (ft_putendl_fd("Error: No parameter expected", 2), EXIT_FAILURE);
	last_exit_status = EXIT_SUCCESS;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, reprompt);
		line = readline(prompt(last_exit_status));
		signal(SIGINT, SIG_IGN);
		if (line == NULL)
			break ;
		if (!is_empty(line))
		{
			last_exit_status = ft_execute(line, env);
			add_history(line);
			printf("$?=%d\n", last_exit_status);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}
