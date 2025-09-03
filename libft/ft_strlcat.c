/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:02:51 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/12 19:18:52 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lendst;

	lendst = ft_strlen(dst);
	i = 0;
	j = 0;
	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	while ((dst[i] != '\0') && (dst[i]) && (i < dstsize - 1))
		i++;
	while ((src[j]) && (i < dstsize - 1))
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (lendst + ft_strlen(src));
}

// #include <stdio.h>
// #include <bsd/string.h>
// int main (void)
// {
// 	char dst[10] = "yo";
// 	char *src = "hey";
// 	char dsti[10] = "yo";
// 	char *srci = "hey";
// 	size_t len = 0;

// 	printf("%zu ma ft\n%zu ft off\n",
// 	ft_strlcat(dst, src, len), strlcat(dsti, srci, len));
// 	printf("%s ma ft\n%s ft off\n", dst, dsti);
// 	//compiler avec le flag -lbsd
// }