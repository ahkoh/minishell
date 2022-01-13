/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:49:37 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:19:24 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	char			*ptr2;
	char			*result;
	unsigned int	a;

	a = 0;
	if (!s)
		return (NULL);
	result = ft_memalloc((size_t)ft_strlen((char *)s) + 1);
	if (!result)
		return (NULL);
	ptr = (char *)s;
	ptr2 = result;
	while (*ptr)
	{
		*ptr2 = f(a, *ptr);
		ptr++;
		ptr2++;
		a++;
	}
	return (result);
}
