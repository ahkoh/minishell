/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shift.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:48:32 by zhliew            #+#    #+#             */
/*   Updated: 2022/01/13 11:48:45 by zhliew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_shift(void *pointer_array)
{
	void	*first;
	void	**array;

	array = (void **)pointer_array;
	first = *array;
	while (*array)
	{
		*array = *(array + 1);
		array++;
	}
	return (first);
}
