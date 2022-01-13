/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:39:56 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:17:53 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int	a;

	if (n < 0)
	{
		a = (unsigned int)(n * -1);
		ft_putchar('-');
	}
	else
		a = (unsigned int)n;
	if (a >= 10)
		ft_putnbr(a / 10);
	ft_putchar((a % 10) + '0');
}
