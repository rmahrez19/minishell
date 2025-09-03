/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:53:12 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 23:20:15 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	manage_input(t_exec *s)
{
	if (s->tmp->type == INPUT && s->tmp->next)
	{
		s->fd = open(s->tmp->next->arg, O_RDONLY);
		if (s->fd == -1)
			perror("open input");
		else
			dup2_and_close_in(s->fd);
	}
	s->tmp = s->tmp->next;
}

void	close_heredoc_fds(t_token *lst)
{
	t_token	*temp;

	temp = lst;
	while (temp)
	{
		if (temp->heredoc_fd > -1)
			close(temp->heredoc_fd);
		temp->heredoc_fd = -1;
		temp = temp->next;
	}
}
