/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:39:53 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 13:52:27 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, const int size)
{
	char			*new;
	unsigned int	a;
	unsigned int	b;

	a = 0;
	b = 0;
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	while (s1[b] != '\0' && b < (unsigned int)size)
	{
		new[b] = s1[b];
		b++;
	}
	new[b] = '\0';
	return (new);
}
