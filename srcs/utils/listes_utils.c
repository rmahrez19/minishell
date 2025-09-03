/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:32:53 by hectordavro       #+#    #+#             */
/*   Updated: 2025/08/07 18:31:08 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*ft_lst_token_new(char *arg, int type, int double_quote, int colle_next)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->arg = arg;
	new_token->type = type;
	new_token->double_quote = double_quote;
	new_token->colle_next = colle_next;
	new_token->heredoc_fd = -1;
	new_token->original_string = NULL;
	new_token->to_expand = 0;
	new_token->next = NULL;
	return (new_token);
}

void	ft_lstadd_token_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_print_lst_token(t_token *lst)
{
	while (lst != NULL)
	{
		printf("arg = %s\n", lst->arg);
		printf("type = %d\n", lst->type);
		printf("colle_next = %d\n", lst->colle_next);
		lst = lst->next;
	}
}
