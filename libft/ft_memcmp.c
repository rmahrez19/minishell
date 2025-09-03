/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:12:58 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:47:08 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1i;
	unsigned char	*s2i;
	size_t			i;

	s1i = (unsigned char *)s1;
	s2i = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1i[i] != s2i[i])
			return (s1i[i] - s2i[i]);
		i++;
	}
	return (0);
}

// #include <string.h>
// #include <stdio.h>
// int main (void)
// {
//     char *s1 = "hello";
//     char *s2 = "heLlo";
//     size_t i = 0;

//     printf("ma ft %d \n ft off %d", ft_memcmp(s1, s2, i),
//     memcmp(s1, s2, i));
// }