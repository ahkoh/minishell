/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:09:18 by skoh              #+#    #+#             */
/*   Updated: 2022/01/13 18:30:36 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

/* helper to close 1 or 2 fd, avoiding STDIN/OUT/ERR */
void	fd_close(int f1, int f2)
{
	if (f1 > STDERR_FILENO)
		close(f1);
	if (f2 > STDERR_FILENO)
		close(f2);
}

// backup before dup2, to allow restore
void	fd_swap(int *fd, int target)
{
	int	swap;

	if (*fd > STDERR_FILENO)
	{
		swap = dup(target);
		dup2(*fd, target);
		close(*fd);
		*fd = swap;
	}
}

// close existing fd before assigning to a new fd
void	fd_replace(int *fd_dest, int fd_src)
{
	if (*fd_dest > STDERR_FILENO)
		close(*fd_dest);
	*fd_dest = fd_src;
}
