/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 14:17:34 by skoh              #+#    #+#             */
/*   Updated: 2022/01/18 10:21:52 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "minishell.h"
#include <sys/stat.h>

// locate executable, handle file exist/permission & execve error

static void	print_error(const char *item, char *error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)item, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(error, STDERR_FILENO);
}

static bool	next_path(char **search, char **dir)
{
	char	*found;

	*dir = NULL;
	if (*search == NULL)
		return (false);
	found = ft_strchr(*search, ':');
	if (found)
	{
		*dir = ft_strndup(*search, found - *search);
		*search = found + 1;
	}
	else
	{
		*dir = ft_strdup(*search);
		*search = NULL;
	}
	return (true);
}

// allow emtpy (current dir) in PATH=":/bin"
static char	*search_path(const char *filename, const char *path,
	struct stat *st)
{
	char		*dup;
	char		*search;
	char		*dir;
	char		*fp;

	search = (dup = ft_strdup(path));
	while (next_path(&search, &dir))
	{
		if (*dir)
			fp = combine_path(dir, filename);
		else
			fp = ft_strdup(filename);
		free(dir);
		if (stat(fp, st) == 0 && S_ISREG(st->st_mode))
			return (free(dup), fp);
		free(fp);
	}
	if (*path)
		print_error(filename, "command not found");
	else
		print_error(filename, strerror(ENOENT));
	ft_bzero(st, sizeof(struct stat));
	free(dup);
	return (NULL);
}

//not strerror(EISDIR) because first character in capital letter
static char	*px_get_fp(const char *filename, const char *path, struct stat *st)
{
	ft_bzero(st, sizeof(struct stat));
	if (path == NULL || ft_strchr(filename, '/'))
	{
		if (stat(filename, st) == -1)
			return (print_error(filename, strerror(ENOENT)), NULL);
		if (S_ISDIR(st->st_mode))
			return (print_error(filename, "is a directory"), NULL);
		return (ft_strdup(filename));
	}
	return (search_path(filename, path, st));
}

// exe-file without path must exist in env-path or Command-not-found
// exe-file with path will use errno
// return permission-denied (dir or execve failed)
// or return not-found (with/without path)
// "Exec format error" with read-perm => run sh to fix missing shebang
int	px_execfile(char **argv, char **env)
{
	char		*fp;
	struct stat	st;
	int			i;
	char		**sh;

	fp = px_get_fp(*argv, get_const_value_by_key(env, "PATH"), &st);
	if (!fp & S_ISDIR(st.st_mode))
		return (126);
	else if (!fp)
		return (127);
	execve(fp, argv, env);
	if (errno == ENOEXEC && st.st_mode & 0444)
	{
		i = 0;
		while (argv[i])
			i++;
		sh = ft_calloc(i + 1, sizeof(char *));
		while (i && i--)
			sh[i + 1] = argv[i];
		sh[0] = "/bin/sh";
		execve(sh[0], sh, env);
		free(sh);
		return (print_error(fp, strerror(errno)), free(fp), 126);
	}
	return (print_error(fp, strerror(EACCES)), free(fp), 126);
}
