/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:43:11 by skoh              #+#    #+#             */
/*   Updated: 2022/01/17 01:15:38 by skoh             ###   ########.fr       */
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

char	*get_value_by_key(char **env, char *key)
{
	const int	len = ft_strlen(key);

	while (*env && len)
	{
		if (ft_strncmp(*env, key, len) == 0 && (*env)[len] == '=')
			return (ft_strdup(*env + len + 1));
		env++;
	}
	return (NULL);
}
