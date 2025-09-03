/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:11:34 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/13 02:15:22 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main (void)
// {
//     char *s = "hello les copains";
//     int c = 108;
//     char *si = "hello les copains";
//     int ci = 108;
//     size_t i = 0;
//     printf("ma ft %s \n ft off %s", (char *)ft_memchr(s,c, i), 
//     (char *)memchr(si,ci , i));
// }
