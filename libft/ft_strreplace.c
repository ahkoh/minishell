/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:32:57 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/14 11:02:34 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strreplace(char **str, char *replace, int size_search, int search_index)
{
	int		a;
	int		b;
	char	*new_str;

	new_str = malloc(sizeof(char)
			* (ft_strlen((*str)) - size_search + ft_strlen(replace) + 1));
	a = -1;
	b = -1;
	while ((*str)[++a] != '\0')
	{
		if (a == search_index)
		{
			while (*replace != '\0')
				new_str[++b] = *(replace++);
			a += size_search;
		}
		if ((*str)[a] == '\0')
			break ;
		new_str[++b] = (*str)[a];
	}
	new_str[++b] = '\0';
	free((*str));
	(*str) = new_str;
	return (ft_strlen(replace));
}
