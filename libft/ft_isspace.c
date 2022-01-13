/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:11 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 13:52:39 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	int		a;
	char	*whitespace;

	a = 0;
	whitespace = " \t\n\v\f\r";
	while (whitespace[a] != '\0')
	{
		if (whitespace[a] == c)
			return (1);
		a++;
	}
	return (0);
}
