/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:39:19 by zhliew            #+#    #+#             */
/*   Updated: 2021/05/17 23:17:46 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *s)
{
	unsigned int	a;

	a = 0;
	if (!s)
		return ;
	while (s[a] != '\0')
	{
		ft_putchar(s[a]);
		a++;
	}
	ft_putchar('\n');
}
