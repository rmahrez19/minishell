/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cat_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:21:43 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 15:10:49 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_nodes_and_replace(t_utils *s, int i)
{
	if (i)
	{
		s->new = s->temp->next;
		s->to_free = s->temp->next->next;
		s->temp = s->temp->next->next->next;
	}
	free(s->to_free->arg);
	free(s->to_free);
	s->new->next = s->temp;
}

void	launch_reorganize_linked_list(t_utils *s)
{
	while (s->temp)
	{
		if (!ft_strcmp(s->temp->arg, "cat") && s->temp->next)
		{
			if (!ft_strcmp(s->temp->next->arg, "<") && s->temp->next->next)
			{
				s->new = s->temp;
				s->to_free = s->temp->next;
				s->temp = s->temp->next->next;
				free_nodes_and_replace(s, 0);
			}
			else if (s->temp->next)
			{
				if (!s->temp->next->next)
					return ;
				if (s->temp->next->arg[0] == '-'
					&& !ft_strcmp(s->temp->next->next->arg, "<")
					&& s->temp->next->next->next)
					free_nodes_and_replace(s, 1);
			}	
		}
		s->temp = s->temp->next;
	}
}

int	is_an_input_in_list(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->arg, "<"))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	reorganize_linked_list(t_token *lst)
{
	t_utils	s;

	s.temp = lst;
	if (is_an_input_in_list(s.temp))
		launch_reorganize_linked_list(&s);
}
