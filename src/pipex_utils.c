/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:17:34 by skoh              #+#    #+#             */
/*   Updated: 2022/01/07 12:33:29 by Koh              ###   ########.kl       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static char	**px_get_env_paths(char **env)
{
	const char	path[] = "PATH";
	const int	len = sizeof(path) / sizeof(*path);

	while (*env && !ft_strnstr(*env, "PATH=", len))
		env++;
	if (*env)
		return (ft_split(*env + len, ':'));
	return (NULL);
}

static char	*px_get_fp(const char *filename, char **env)
{
	char		**paths;
	const int	filename_len = ft_strlen(filename);
	char		*filepath;
	int			filepath_size;
	int			i;

	paths = px_get_env_paths(env);
	i = -1;
	while (paths && paths[++i])
	{
		filepath_size = ft_strlen(paths[i]) + filename_len + 2;
		filepath = malloc(filepath_size);
		ft_strlcpy(filepath, paths[i], filepath_size);
		ft_strlcat(filepath, "/", filepath_size);
		ft_strlcat(filepath, filename, filepath_size);
		if (access(filepath, X_OK) == 0)
			return (ft_split_free(&paths), filepath);
		free(filepath);
	}
	ft_split_free(&paths);
	if (ft_strchr(filename, '/'))
		return (ft_strdup(filename));
	return (NULL);
}

// exe-file without path must exist in env-path or Command-not-found
// exe-file with path will use errno
int	px_execfile(char *command, char **env)
{
	char	**argv;
	char	*fp;

	argv = ft_split(command, ' ');
	fp = px_get_fp(*argv, env);
	if (fp)
		execve(fp, argv, env);
	if (!fp || (errno == 2 && !ft_strchr(*argv, '/')))
		ft_printf_fd(2, "pipex: command not found: %s\n", *argv);
	else
		ft_printf_fd(2, "pipex: %s: %s\n", strerror(errno), *argv);
	ft_split_free(&argv);
	free(fp);
	if (!fp || errno == 2)
		return (127);
	if (errno == 13)
		return (126);
	return (EXIT_FAILURE);
}

static int	px_openfile(char *filename, int stdio, int is_bonus)
{
	int	fd;

	if (stdio == STDOUT_FILENO && !is_bonus)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (stdio == STDOUT_FILENO && is_bonus)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n",
				strerror(errno), filename), 0);
	dup2(fd, stdio);
	close(fd);
	return (1);
}

int	px_replace_stdio(int *io, char *infile, char *outfile, int is_bonus)
{
	if (io[0])
		dup2(io[0], STDIN_FILENO);
	else if (!px_openfile(infile, STDIN_FILENO, is_bonus))
		return (0);
	if (io[1])
		dup2(io[1], STDOUT_FILENO);
	else if (!px_openfile(outfile, STDOUT_FILENO, is_bonus))
		return (0);
	return (1);
}
