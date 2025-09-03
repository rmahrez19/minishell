/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:37:11 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/08 00:38:04 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	new -> next = *lst;
	*lst = new;
}

// #include <stdio.h>
// int main (void)
// {
// 	int content1 = 10 ;
// 	int content2 = 9;
// 	t_list *list = ft_lstnew(&content1);
// 	printf("premier element %d", *(int *)list->content);
// 	t_list *new = ft_lstnew(&content2);
// 	ft_lstadd_front(&list, new);
// 	printf("element 1 %d", *(int *)list->content);
// 	printf("element 2 %d", *(int *)list->next->content);
// }
