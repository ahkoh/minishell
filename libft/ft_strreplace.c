/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:32:57 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/17 11:05:19 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	add_replace(char *replace, char **new_str, int *b, int size_search)
{
	int	i;

	i = 0;
	while (replace[i] != '\0')
	{
		(*new_str)[++*b] = replace[i];
		i++;
	}
	return (size_search);
}

int	ft_strreplace(char **str, char *replace, int size_search, int search_index)
{
	int		a;
	int		b;
	int		replace_size;
	char	*new_str;

	replace_size = ft_strlen(replace);
	new_str = malloc(sizeof(char)
			* (ft_strlen((*str)) - size_search + replace_size + 1));
	a = -1;
	b = -1;
	while ((*str)[++a] != '\0')
	{
		if (a == search_index)
			a += add_replace(replace, &new_str, &b, size_search);
		if ((*str)[a] == '\0')
			break ;
		new_str[++b] = (*str)[a];
	}
	if (a == search_index)
		add_replace(replace, &new_str, &b, size_search);
	new_str[++b] = '\0';
	free((*str));
	(*str) = new_str;
	return (replace_size);
}
