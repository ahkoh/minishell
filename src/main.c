#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "libft.h"

static void	handle_ctrl_c(int signum)
{
	(void) signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*ft_strcat(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	return (dest);
}

int	cd(char *line)
{
	if (ft_strnstr(line, "cd ", ft_strlen(line)) == line)
		return (!chdir(line + 3));
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	ctrl_d;
	char	cwd[512] = {"minishell:"};

	(void) argc;
	(void) argv;
	(void) env;
	signal(SIGINT, handle_ctrl_c);
	while (1)
	{
		getcwd(cwd + 10, 500);
		ft_strlcat(cwd, "> ", 512);
		line = readline(cwd);
		ctrl_d = line == NULL;
		if (ctrl_d)
			return (free(line), EXIT_SUCCESS);
		cd(line);
		add_history(line);
		free(line);
	}
	return (EXIT_SUCCESS);
}
