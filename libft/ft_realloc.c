/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/02/07 18:21:54 by lobriott          #+#    #+#             */
/*   Updated: 2025/02/07 18:21:54 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_realloc(char *memoryarea, size_t newsize)
{
	char		*newmemoryarea;
	size_t		oldsize;

	if (memoryarea)
		oldsize = ft_strlen(memoryarea);
	else
		oldsize = 0;
	newmemoryarea = (char *)malloc(oldsize + newsize + 1);
	if (!newmemoryarea)
		return (NULL);
	if (memoryarea)
	{
		ft_memcpy(newmemoryarea, memoryarea, oldsize);
		free(memoryarea);
	}
	ft_memset(newmemoryarea + oldsize, 0, newsize + 1);
	return (newmemoryarea);
}

// int main (void)
// {
// 	char *str;

// 	str = malloc (sizeof(char)*2);
// 	str [0] = 'a';
// 	str [1] = '\0';
// 	str = ft_realloc(str, 2, 3);
// 	str [1] = 'a';
// 	str [2] = '\0';
// 	ft_printf("%s\n", str);
// 	free(str);
// }
