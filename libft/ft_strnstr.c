/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:01:44 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/13 01:47:39 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && needle[j] != '\0' && i < len)
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			while (haystack[i + j] == needle[j] && (i + j) < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

// #include <bsd/string.h>
// #include <stdio.h>
// int main (void)
// {
// 	char *needle = "aaabcabcd";
// 	char *haystack = "aabc";
// 	size_t i = 3;
// 	printf("ma fonction : %s \n", ft_strnstr(haystack,needle,i));
// 	printf("fonction officielle : %s",
// strnstr(haystack,needle,i));
// }
