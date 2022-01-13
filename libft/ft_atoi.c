/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 15:39:40 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:14:31 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	a;
	int				neg;
	int				num;

	a = 0;
	neg = 0;
	num = 0;
	while (str[a] == ' ' || str[a] == '\t' || str[a] == '\n'
		|| str[a] == '\v' || str[a] == '\f' || str[a] == '\r')
		a++;
	if (str[a] == '+' || str[a] == '-')
	{
		if (str[a] == '-')
			neg = 1;
		a++;
	}
	while (str[a] != '\0' && (str[a] >= '0' && str[a] <= '9'))
	{
		num = (num * 10) + (str[a] - '0');
		a++;
	}
	if (neg == 1)
		num = num * -1;
	return (num);
}
