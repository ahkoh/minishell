/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:31:29 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:17:25 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				a;
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	a = 0;
	if (n == 0 || dst == src)
		return (dst);
	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	while (a < n)
	{
		ptr1[a] = ptr2[a];
		a++;
	}
	return (dst);
}
