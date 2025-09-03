/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:01:28 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:48:43 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (unsigned char)c)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int main (void)
// {
//     char *str = "hello les bebews";

//     printf("%s \n", ft_strrchr(str,'t' + 256));
// 	printf("%s", ft_strrchr(str,'t' + 256));
// }