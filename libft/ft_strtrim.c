/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:47:14 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/13 15:47:14 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char c, char *s)
{
	int	a;

	a = 0;
	while (s[a] != '\0')
	{
		if (s[a] == c)
			return (1);
		a++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		len;
	int		a;

	if (!s1 || !set)
		return (NULL);
	a = 0;
	while (s1[a] && ft_search((char)s1[a], (char *)set))
		a++;
	len = ft_strlen((char *)s1);
	while (len > 0 && ft_search((char)s1[len - 1], (char *)set))
		len--;
	len = len - a;
	if (len < 0)
		len = 0;
	i = -1;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (++i < len)
		res[i] = s1[i + a];
	res[i] = '\0';
	return (res);
}
