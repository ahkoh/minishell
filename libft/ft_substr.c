/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:45:47 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/13 15:45:47 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	size;
	unsigned int	a;
	char			*sub;

	sub = malloc(sizeof(char) * (len + 1));
	if (!s || !sub)
		return (NULL);
	a = 0;
	size = ft_strlen(s);
	while (a < len && a + start < size)
	{
		sub[a] = s[a + start];
		a++;
	}
	while (a <= len)
	{
		sub[a] = '\0';
		a++;
	}
	return (sub);
}
