/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:09:18 by skoh              #+#    #+#             */
/*   Updated: 2022/01/14 09:44:51 by skoh             ###   ########.fr       */
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

// close existing fd before assigning to a new fd
void	fd_replace(int *fd_dest, int fd_src)
{
	if (*fd_dest > STDERR_FILENO)
		close(*fd_dest);
	*fd_dest = fd_src;
}

static void	fd_dup(int *fd, int io, bool dup_io)
{
	int	swap;

	if (*fd <= STDERR_FILENO)
		return ;
	if (dup_io)
		swap = dup(io);
	dup2(*fd, io);
	close(*fd);
	if (dup_io)
		*fd = swap;
	else
		*fd = io;
}

void	fd_dup_io(int *fin, int *fout, bool dup_io)
{
	fd_dup(fin, STDIN_FILENO, dup_io);
	fd_dup(fout, STDOUT_FILENO, dup_io);
}
