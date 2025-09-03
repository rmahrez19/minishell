/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 00:00:06 by hectordavro       #+#    #+#             */
/*   Updated: 2025/08/12 15:56:47 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_parsing(char *input)
{
	t_token	*lst;

	if (!check_quotes_closed(input))
	{
		ft_printf(RED "QUOTE NOT CLOSED\n" RESET);
		free(input);
		return (NULL);
	}
	lst = ft_tokenize(input);
	fix_cmd_typing(lst);
	free(input);
	return (lst);
}

void	fix_cmd_typing(t_token *lst)
{
	while (lst && lst->type != PIPE)
	{
		if (lst->type == INPUT || lst->type == TRUNC
			|| lst->type == APPEND || lst->type == HEREDOC)
		{
			if (lst->next)
				lst = lst->next;
		}
		else if (lst->type == ARG)
		{
			lst->type = CMD;
			break ;
		}
		lst = lst->next;
	}
}
