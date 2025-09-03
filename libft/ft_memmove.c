/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:25:18 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/12 20:27:02 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*tabdst;
	char	*tabsrc;

	tabdst = (char *) dest;
	tabsrc = (char *) src;
	if (!src && !dest)
		return (NULL);
	i = 0;
	if (tabdst > tabsrc)
	{
		while (len-- > 0)
			tabdst[len] = tabsrc[len];
	}
	else
	{
		while (i < len)
		{
			tabdst[i] = tabsrc[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <string.h>
#include <stdio.h>
int main (void)
{
char src[] = "Holl";
char dst[] = "heyhey";
char src1[] = "Holl";
char dst1[] = "heyhey";
size_t len = 5;
printf("%s \n", (char *)ft_memmove(dst, src, len));
printf("%s \n", (char *)memmove(dst1, src1, len));
int i = 0;
int src[5] = {2 , 2 , 2 , 2 , 2};
int dst[5] = {3 , 3 , 3 , 3 , 3};
int srci[5] = {2 , 2 , 2 , 2 , 2};
int dsti[5] = {3 , 3 , 3 , 3 , 3 };
size_t len = 3;
ft_memmove(dst, src, len);
while (i < 5)
{
printf("[%d]", dst[i]);
i++;
}
printf("\n");
i = 0;
ft_memmove(dsti, srci, len);
while (i < 5)
{
printf("[%d]", dsti[i]);
i++;
}
}
*/
