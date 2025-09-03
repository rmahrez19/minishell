/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:11:52 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/03 16:18:24 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_fds(int fd1, int fd2, int fd3, int to_dup)
{
	if (to_dup != -1)
		dup2(to_dup, STDOUT_FILENO);
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
	if (fd3 != -1)
		close(fd3);
}
