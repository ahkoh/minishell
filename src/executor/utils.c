/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:43:11 by skoh              #+#    #+#             */
/*   Updated: 2022/01/14 15:50:35 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <sys/stat.h>
#include <unistd.h>

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

bool	is_executable(char *fp)
{
	struct stat	buf;

	if (stat(fp, &buf) == -1)
		return (false);
	return (S_ISREG(buf.st_mode) && buf.st_mode & 0111);
}
