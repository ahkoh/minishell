/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:44:41 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:19:06 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*new;
	unsigned int	a;
	unsigned int	b;

	a = 0;
	b = 0;
	while (s1[a] != '\0')
		a++;
	new = (char *)malloc(sizeof(char) * (a + 1));
	if (!new)
		return (NULL);
	while (s1[b] != '\0')
	{
		new[b] = s1[b];
		b++;
	}
	new[b] = '\0';
	return (new);
}
