/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 23:43:11 by skoh              #+#    #+#             */
/*   Updated: 2022/01/10 01:24:40 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* shift first item from null-terminated pointer-array eg argv, envp */
/* first item is removed and returned, while items N become items N-1 */
void	*ft_shift(void *pointer_array)
{
	void	*first;
	void	**array;

	array = (void **)pointer_array;
	first = *array;
	while (*array)
	{
		*array = *(array + 1);
		array++;
	}
	return (first);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == s2)
		return (0);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

bool	ft_isempty(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line++))
			return (false);
	}
	return (true);
}
