/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 21:41:51 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:34:37 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dup2_and_close_out(int fd)
{
	dup2(fd, STDOUT_FILENO);
	if (fd != -1)
		close(fd);
}

void	dup2_and_close_in(int fd)
{
	dup2(fd, STDIN_FILENO);
	if (fd != -1)
		close(fd);
}

void	close_all_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}

void	cafd(void)
{
	int	fd;

	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}
