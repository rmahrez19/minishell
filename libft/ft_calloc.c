/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:11:48 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/12 03:49:08 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	bytes;
	void	*ptr;

	bytes = count * size;
	if (size && ((bytes / size) != count))
		return (NULL);
	ptr = malloc(bytes);
	if (NULL == ptr)
		return (NULL);
	ft_bzero(ptr, bytes);
	return (ptr);
}

// #include <stdio.h>
// int main (void)
// {
// 	size_t count = 5;
// 	size_t size = 6;
// 	char *empty = ft_calloc(count, size);
// 	size_t i = 0;

// 	while(i < size && empty[i] == 0)
// 		i++;
// 	if (i < size)
// 		printf("error");
// 	else
// 		printf("success \n valeur de i = %zu \n valeur de size = %zu", i, size);
// }
