/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:38:24 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:19:43 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *find, size_t len)
{
	unsigned int	a;
	unsigned int	b;

	if (!*find)
		return ((char *)src);
	a = 0;
	while (src[a] != '\0' && (size_t)a < len)
	{
		if (src[a] == find[0])
		{
			b = 1;
			while (find[b] != '\0' && src[a + b] == find[b]
				&& (size_t)(a + b) < len)
				b++;
			if (find[b] == '\0')
				return ((char *)&src[a]);
		}
		a++;
	}
	return (0);
}
