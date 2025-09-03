/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:41:20 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/08 00:42:29 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (del == NULL || lst == NULL)
		return ;
	del(lst->content);
	free(lst);
}

// void delete(void *tosupp)
// {
// 	int *supp = (int *)tosupp;
// 	if(*supp != 0)
// 		return ;
// 	supp = 0;
// }

// #include <stdio.h>
// int main (void)
// {
// 	int t1 = 12;
// 	int t2 = 8;

// 	t_list *list = ft_lstnew(&t1);
// 	t_list *toadd = ft_lstnew(&t2);
// 	ft_lstadd_back(&list, toadd);
// 	printf("[%d] element 1\n", *(int *)list->content);
// 	printf("[%d] element 2\n", *(int *)list->next->content);
// 	ft_lstdelone(list->content, &delete);
// 	printf("[%d] element 1\n", *(int *)list->next->content);
// 	printf("[%d] element 1\n", *(int *)list->content);
// }