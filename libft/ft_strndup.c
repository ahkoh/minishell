/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:39:53 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/20 08:50:50 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, const int size)
{
	char			*new;
	unsigned int	b;

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
