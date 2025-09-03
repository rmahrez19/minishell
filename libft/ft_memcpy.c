/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:23:51 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/12 04:10:38 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dsti;
	unsigned char	*srci;

	dsti = (unsigned char *)dest;
	srci = (unsigned char *)src;
	if (n == 0)
		return (dest);
	if (!src && !dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dsti[i] = srci[i];
		i++;
	}
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// int main (void)
// {
// 	char dest[] = "coucou";
// 	char src[] = "hello";
// 	char desti[] = "coucou";
// 	char srci[] = "hello";
// 	size_t len = 4;
// 	ft_memcpy(dest, src, len);
// 	memcpy(desti, srci, len);
// 	printf("%s | ma ft \n %s | ft officielle ", dest, desti);
// 	return (0);
// }