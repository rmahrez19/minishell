/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:42:49 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/08 00:44:25 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*todo;
	t_list	*suivant;

	if (lst == NULL || f == NULL)
		return ;
	todo = lst;
	while (todo != NULL)
	{
		suivant = todo -> next;
		f(todo -> content);
		todo = suivant;
	}
}

// #include <stdio.h>
// void modif(void *tomod)
// {
// 	*(int *)tomod *= 10;
// }

// int main (void)
// {
// 	int a = 5;
// 	int b = 6;
// 	t_list *list = ft_lstnew(&a);
// 	t_list *new = ft_lstnew(&b);
// 	ft_lstadd_back(&list, new);
// 	printf("[%d] valeur 1\n", *(int *)list->content);
// 	printf("[%d] valeur 1\n", *(int *)list->next->content);
// 	ft_lstiter(list, &modif);
// 	printf("[%d] valeur 1\n", *(int *)list->content);
// 	printf("[%d] valeur 1\n", *(int *)list->next->content);
// }