/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 18:37:41 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/30 19:19:27 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	ft_free(void)
{
	ft_malloc(0);
}

void	ft_free_list(t_list *list)
{
	t_list	*tmp;

	while (list != NULL)
	{
		tmp = list;
		if (list)
			free(list->content);
		list = list->next;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}

void	*ft_malloc(size_t size)
{
	void			*ptr;
	static t_list	*adr = NULL;

	if (size == 0)
	{
		ft_free_list(adr);
		adr = NULL;
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size);
	ft_lstadd_front(&adr, ft_lstnew(ptr));
	return (ptr);
}
