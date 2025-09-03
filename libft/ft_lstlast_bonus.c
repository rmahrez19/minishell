/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:44:47 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/08 00:45:39 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lastone;

	if (lst == NULL)
		return (lst);
	lastone = lst;
	while (lastone -> next != NULL)
		lastone = lastone -> next;
	return (lastone);
}

// #include <stdio.h>
// int main (void)
// {
// 	int a = 12;
// 	int b = 15;
// 	t_list *list = ft_lstnew(&a);
// 	t_list *suivant = ft_lstnew(&b);
// 	ft_lstadd_back(&list, suivant);
// 	printf("[%d] \n[%d]\n", *(int *)list->content, *(int *)list->next->content);
// 	printf("[%d]", *(int *)ft_lstlast(list)->content);
// }