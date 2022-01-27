/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 21:00:37 by skoh              #+#    #+#             */
/*   Updated: 2022/01/28 04:57:26 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static long	ft_atol(const char *str)
{
	long	sum;
	long	prev;
	int		is_negative;

	prev = (is_negative = (sum = 0));
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		is_negative = (*str++ == '-');
	while (ft_isdigit(*str))
	{
		if (is_negative)
			sum = sum * 10 - (*str++ - '0');
		else
			sum = sum * 10 + (*str++ - '0');
		if (sum / 10 == prev)
			prev = sum;
		else
			return (-!is_negative);
	}
	return (sum);
}

// fixed: allowed space/tab after number, no overflow for "-0"
long	ft_atol_try(const char *str, long *out)
{
	*out = ft_atol(str);
	while (ft_isspace(*str))
		str++;
	if (*out == -(*str != '-') && ft_strlen(str) > 17)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!ft_isdigit(*str))
		return (0);
	while (ft_isdigit(*str))
		str++;
	while (*str == ' ' || *str == '\t')
		str++;
	return (*str == '\0');
}

// cleanup_heredocs() is called before quit()
// exit return $? unless number argument provided
// "exit <num> <extra>"" print error and does not exit!
int	quit(char **argv, t_prompt *prompt)
{
	long	exit_status;

	(void)prompt;
	exit_status = prompt->e_status;
	if (argv[1])
	{
		if (!ft_atol_try(argv[1], &exit_status))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_status = 255;
		}
		else if (argv[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	write(STDIN_FILENO, "exit\n", 5);
	cleanup(prompt);
	exit((int)exit_status);
}
