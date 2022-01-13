/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:37:48 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/18 01:16:42 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	a;

	a = 1;
	while (*s)
	{
		s++;
		a++;
	}
	while (*s != (char)c && a > 0)
	{
		s--;
		a--;
	}
	if (a == 0)
		return (NULL);
	return ((char *)s);
}
