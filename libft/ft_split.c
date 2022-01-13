/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:47:58 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/13 15:47:58 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_split(char *s, char c)
{
	int	a;
	int	count;

	a = 0;
	count = 0;
	while (s[a] != '\0' && s[a] == c)
		a++;
	if (a == 0)
	{
		a = 1;
		count++;
	}
	while (s[a])
	{
		if (s[a - 1] == c && s[a] != c)
			count++;
		a++;
	}
	return (count);
}

static char	**ft_get_array(char *str, char c, int split_count, int count)
{
	int		i;
	char	**array;

	i = -1;
	array = malloc(sizeof(char *) * (split_count + 1));
	if (!array)
		return (NULL);
	while (++i < split_count && *str)
	{
		while (*str == c && *str)
			str++;
		while (*str != c && *str)
		{
			count++;
			str++;
		}
		array[i] = malloc(sizeof(char) * (count + 1));
		if (!array[i])
			return (NULL);
		if (count == 0)
			array[i] = 0;
		count = 0;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	int		split;
	char	**array;

	i = -1;
	if (!s)
		s = "";
	split = ft_get_split((char *)s, c);
	array = ft_get_array((char *)s, c, split, 0);
	if (!array)
		return (NULL);
	while (++i < split && *s && array[i])
	{
		count = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			array[i][count] = *(s++);
			count++;
		}
		array[i][count] = '\0';
	}
	return (array);
}
