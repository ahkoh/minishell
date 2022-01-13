/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_qsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:52:28 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 13:52:10 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static int	partition(char **av, int low, int high)
{
	char	*string_pivot;
	int		x;
	int		y;

	string_pivot = av[high];
	x = low;
	y = low;
	while (y <= high - 1)
	{
		if (ft_strcmp(av[y], string_pivot) < 0)
		{
			swap(&av[x], &av[y]);
			x++;
		}
		y++;
	}
	swap(&av[x], &av[high]);
	return (x);
}

void	ft_str_qsort(char **av, int low, int high)
{
	int	p;

	if (low < high)
	{
		p = partition(av, low, high);
		ft_str_qsort(av, low, p - 1);
		ft_str_qsort(av, p + 1, high);
	}
}
