/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:43:11 by skoh              #+#    #+#             */
/*   Updated: 2022/01/16 12:41:42 by skoh             ###   ########.fr       */
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
