/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 23:11:09 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/04 16:44:39 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	checking_heredoc(t_token *lst)
{
	while (lst)
	{
		if (lst->type == HEREDOC)
		{
			if (!lst->next)
				return (print_unexpected("newline"), 1);
		}
		lst = lst->next;
	}
	return (0);
}

static void	launch_handle_redirections_heredoc(t_exec *s)
{
	while (s->tmp && s->tmp->type != PIPE)
	{
		if (s->tmp->type == HEREDOC && s->tmp->heredoc_fd != -1)
		{
			if (dup2(s->tmp->heredoc_fd, STDIN_FILENO) == -1)
				perror("dup2 heredoc");
			close(s->tmp->heredoc_fd);
			s->tmp->heredoc_fd = -1;
		}
		else if (s->tmp->type == INPUT && s->tmp->next)
		{
			s->fd = open(s->tmp->next->arg, O_RDONLY);
			if (s->fd == -1)
				perror("open infile");
			else
			{
				if (dup2(s->fd, STDIN_FILENO) == -1)
					perror("dup2 infile");
				close(s->fd);
			}
		}
		s->tmp = s->tmp->next->next;
	}
}

void	handle_redirections_heredoc(t_token *start)
{
	t_exec	s;

	s.tmp = start;
	launch_handle_redirections_heredoc(&s);
}
