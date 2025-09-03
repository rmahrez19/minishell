/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:49:27 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:47:21 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*nodes;

	i = 0;
	nodes = lst;
	while (nodes != NULL)
	{
		i++;
		nodes = nodes -> next;
	}
	return (i);
}

// #include <stdio.h>
// int main (void)
// {
// 	int a = 12;
// 	int b = 15;

// 	t_list *list = ft_lstnew(&a);
// 	t_list *new = ft_lstnew(&b);
// 	ft_lstadd_back(&list, new);
// 	printf("[%d]\n[%d]\n", *(int *)list ->content,
// 	*(int *)list ->next->content);
// 	printf("%d", ft_lstsize(list));
// }