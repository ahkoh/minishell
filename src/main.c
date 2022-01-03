/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <skoh@student.42kl.edu.my>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 04:18:29 by Koh               #+#    #+#             */
/*   Updated: 2022/01/04 04:38:35 by Koh              ###   ########.kl       */
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

static void	handle_ctrl_c(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	cd(char *line)
{
	if (ft_strnstr(line, "cd ", ft_strlen(line)) == line)
	{
		if (chdir(line + 3))
		{
			perror(line);
			return (-1);
		}
		return (1);
	}
	return (0);
}

static char	*prompt(char *buf, size_t size, bool has_error)
{
	int	len;

	ft_strlcpy(buf, "minishell:", size);
	len = ft_strlen(buf);
	getcwd(buf + len, size - len);
	if (has_error)
		ft_strlcat(buf, "! ", size);
	else
		ft_strlcat(buf, "> ", size);
	return (buf);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	bool	is_ctrl_d;
	char	cwd[512];
	bool	has_error;

	(void) argc;
	(void) argv;
	(void) env;
	has_error = false;
	signal(SIGINT, handle_ctrl_c);
	while (1)
	{
		line = readline(prompt(cwd, 512, has_error));
		is_ctrl_d = line == NULL;
		if (is_ctrl_d)
			return (free(line), EXIT_SUCCESS);
		has_error = cd(line) == -1;
		add_history(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
