/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:30:48 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 22:03:02 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	launch_creation_output(t_parsing *s, t_data *data)
{
	s->expanded = expand_variables(s->temp->next->arg, data);
	if (!s->expanded)
		return ;
	s->fd = open(s->expanded, which_flags(s->temp), 0644);
	if (s->fd == -1)
		data->bad_fd = -1;
	else
		close(s->fd);
	free(s->expanded);
	s->temp = s->temp->next->next;
}

int	launch_creation(t_data *data, t_parsing *s)
{
	while (s->temp)
	{
		if (s->temp->type == TRUNC || s->temp->type == APPEND)
			launch_creation_output(s, data);
		else if (s->temp->type == INPUT)
		{
			s->expanded = expand_variables(s->temp->next->arg, data);
			s->fd = open(s->expanded, O_RDONLY);
			if (s->fd == -1)
				return (print_invalid_file(s->expanded), 1);
			else
				close (s->fd);
			free(s->expanded);
			s->temp = s->temp->next->next;
		}
		else
			s->temp = s->temp->next;
	}
	return (0);
}

int	create_redirection_file(t_token *lst, t_data *data)
{
	t_parsing	s;

	s.temp = lst;
	return (launch_creation(data, &s));
}

int	move_i(int i, char *line, char c)
{
	i += 2;
	while (line[i])
	{
		if (line[i] == c)
			break ;
		i++;
	}
	return (i - 1);
}
