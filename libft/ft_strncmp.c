/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:02:09 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:48:36 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0' && i != n - 1)
		i++;
	if (!*s1 && !s2)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// #include <string.h>
// #include <stdio.h>
// int main (void)
// {
//     printf("ma ft => %d \n", ft_strncmp("test\200", "test\0", 6));
//     printf("ft originale => %d", strncmp("test\200", "test\0", 6));
// }
