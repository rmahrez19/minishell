/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:39:39 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/13 02:17:45 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*suivant;

	if (lst == NULL || del == NULL)
		return ;
	while (lst && *lst)
	{
		suivant = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = suivant;
	}
}

// void delete(void *tosupp)
// {
// 	unsigned char *supp;
// 	supp = (unsigned char *)tosupp;
// 	int i = 0;
// 	while (supp[i] != 0)
// 	{
// 		supp[i] = 0;
// 		i++;
// 	}
// }
// #include <stdio.h>
// int main (void)
// {
// 	int t1 = 12;
// 	int t2 = 8;
// 	t_list *list = ft_lstnew(&t1);
// 	t_list *toadd = ft_lstnew(&t2);
// 	ft_lstadd_back(&list, toadd);
// 	printf("[%d] ellement 1\n", *(int *)list->content);
// 	printf("[%d] ellement 2\n", *(int *)list->next->content);
// 	ft_lstclear(&list, &delete);
// 	printf("[%d] ellement 1\n", *(int *)list->content);
// }
