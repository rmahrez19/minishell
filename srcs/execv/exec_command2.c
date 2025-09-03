/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:06:29 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:13:42 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	opening_redir_file(t_exec *s, t_token *lst)
{
	s->something_opened++;
	s->fd = open(s->expanded, which_flags(lst), 0644);
	free(s->expanded);
}

int	handle_redirections_cmd(t_token *lst, t_data *data)
{
	t_exec	s;

	s.something_opened = 0;
	while (lst)
	{
		if ((lst->type == TRUNC || lst->type == APPEND) && lst->next)
		{
			s.expanded = expand_variables(lst->next->arg, data);
			if (s.expanded)
				opening_redir_file(&s, lst);
			else
				s.fd = open(lst->next->arg, which_flags(lst), 0644);
			if (s.fd != -1)
				dup2_and_close_out(s.fd);
			else
			{
				ft_putstr_fd("minishell: ", 2);
				perror(lst->next->arg);
				return (-1);
			}
		}
		lst = lst->next;
	}
	return (s.something_opened);
}

int	which_flags(t_token *lst)
{
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if ((lst->type == TRUNC || lst->type == APPEND) && lst->next)
	{
		flags = O_CREAT | O_WRONLY;
		if (lst->type == TRUNC)
			flags |= O_TRUNC;
		else
			flags |= O_APPEND;
	}
	return (flags);
}

int	open_and_free(t_token *lst, t_data *data)
{
	char	*expanded;
	int		fd;

	expanded = expand_variables(lst->next->arg, data);
	if (lst->next->arg[0] == '$')
		fd = open(lst->next->arg + 1, which_flags(lst), 0644);
	else
		fd = open(expanded, which_flags(lst), 0644);
	free(expanded);
	if (fd < 0)
		return (ft_putstr_fd("minishell: ", 2), perror(lst->next->arg), -1);
	return (fd);
}

void	init_struct(t_exec *s, t_token *lst)
{
	s->start = lst;
	s->has_prev_pipe = 0;
	s->pid_count = 0;
	s->i = 0;
}
