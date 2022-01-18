/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:43:11 by skoh              #+#    #+#             */
/*   Updated: 2022/01/18 07:01:41 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

bool	ft_isempty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line++))
			return (false);
	}
	return (true);
}

void	ft_split_free(char ***tab)
{
	int	i;

	if (*tab)
	{
		i = 0;
		while ((*tab)[i])
			free((*tab)[i++]);
		free(*tab);
		*tab = NULL;
	}
}

// get pointer to value by key. do not free pointer
const char	*get_const_value_by_key(char **env, const char *key)
{
	const int	len = ft_strlen(key);

	while (*env && len)
	{
		if (ft_strncmp(*env, key, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}

// must ended '/' to work
static char	*trim_path(char *c)
{
	const int	l = ft_strlen(c);
	int			i;
	int			j;

	i = 0;
	while (c[i])
	{
		if (ft_strncmp(c + i, "//", 2) == 0)
			ft_strlcpy(c + i, c + i + 1, l);
		else if (ft_strncmp(c + i, "/./", 3) == 0)
			ft_strlcpy(c + i, c + i + 2, l);
		else if (ft_strncmp(c + i, "/../", 4) == 0)
		{
			j = i + 3;
			while (i > 0 && i--)
				if (c[i] == '/')
					break ;
			ft_strlcpy(c + i, c + j, l);
		}
		else if (i && c[i] == '/' && c[i + 1] == '\0')
			c[i] = '\0';
		else
			i++;
	}
	return (c);
}

char	*combine_path(const char *a, const char *b)
{
	char	*x;
	char	*y;

	x = ft_strjoin(a, "/");
	y = ft_strjoin(x, b);
	free(x);
	x = ft_strjoin(y, "/");
	free(y);
	return (trim_path(x));
}
