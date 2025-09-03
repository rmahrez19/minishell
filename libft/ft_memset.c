/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:58:34 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:46:25 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)b;
	str = b;
	while (len)
	{
		*str = (unsigned char)c;
		str++;
		len--;
	}
	return (b);
}

/*#include <stdio.h>
#include <string.h>
int main (void)
{
	int c = 66;
	size_t len = 5;
	char *s1[6] ;
	char *s2[6];

// 	printf("ma ft %s \n ft off %s", (char *)ft_memset(s1, c, len)
// 	, (char *)memset(s2, c, len));
// }*/
