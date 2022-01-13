/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:46:37 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/13 15:46:37 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*tmp;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[a])
		a++;
	while (s2[b])
		b++;
	s3 = (char *)malloc(sizeof(char) * (a + b + 1));
	if (!s3)
		return (NULL);
	tmp = s3;
	while (*s1 != '\0')
		*(tmp++) = *(s1++);
	while (*s2 != '\0')
		*(tmp++) = *(s2++);
	*tmp = '\0';
	return (s3);
}
