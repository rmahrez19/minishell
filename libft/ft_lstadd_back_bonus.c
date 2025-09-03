/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:32:43 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/08 00:36:54 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lastone;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lastone = *lst;
	while (lastone -> next != NULL)
		lastone = lastone -> next;
	lastone -> next = new;
}

// #include <stdio.h>
// int main (void)
// {
// 	int content1 = 10 ;
// 	int content2 = 9;
// 	t_list *list = ft_lstnew(&content1);
// 	printf("premier element %d", *(int *)list->content);
// 	t_list *new = ft_lstnew(&content2);
// 	ft_lstadd_back(&list, new);
// 	printf("element suivant %d", *(int *)list->next ->content);
// }