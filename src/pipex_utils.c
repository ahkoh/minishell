/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:17:34 by skoh              #+#    #+#             */
/*   Updated: 2022/01/10 01:43:31 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

// todo replace access()
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
int	px_execfile(char **argv, char **env)
{
	char	*fp;

	fp = px_get_fp(*argv, env);
	if (fp)
		execve(fp, argv, env);
	if (!fp || (errno == 2 && !ft_strchr(*argv, '/')))
		ft_printf_fd(2, "minishell: command not found: %s\n", *argv);
	else
		ft_printf_fd(2, "minishell: %s: %s\n", strerror(errno), *argv);
	free(fp);
	if (!fp || errno == ENOENT)
		return (127);
	if (errno == EACCES)
		return (126);
	return (EXIT_FAILURE);
}
