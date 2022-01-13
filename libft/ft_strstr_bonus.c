/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:43:31 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:19:53 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *find)
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	if (!*find)
		return ((char *)src);
	while (src[a] != '\0')
	{
		if (src[a] == find[0])
		{
			b = 1;
			while (find[b] != '\0' && src[a + b] == find[b])
				b++;
			if (find[b] == '\0')
				return ((char *)&src[a]);
		}
		a++;
	}
	return (0);
}
