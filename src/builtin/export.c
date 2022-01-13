/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 03:07:29 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 16:21:03 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"

int	mini_export(t_prompt *prompt, char **argv);

bool	export(char **argv, t_prompt *prompt, int *exit_status)
{
	if (ft_strcmp(*argv, "export") == 0)
	{
		*exit_status = EXIT_SUCCESS;
		mini_export(prompt, argv + 1);
		return (true);
	}
	return (false);
}
