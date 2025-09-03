/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:48:03 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:47:24 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newlist;

	newlist = malloc(sizeof(t_list));
	if (newlist == NULL)
		return (newlist);
	newlist -> content = content;
	newlist -> next = NULL;
	return (newlist);
}

// #include <stdio.h>
// int main (void)
// {
// 	int content[1] = {10} ;
// 	t_list *list = ft_lstnew(content);
// 	printf("%d", *(int *)list->content);
// }