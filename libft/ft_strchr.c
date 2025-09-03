/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:03:46 by lobriott          #+#    #+#             */
/*   Updated: 2025/02/13 14:08:20 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main (void)
// {
//     char *str = "tripouille";

//     printf("%s yeah\n", ft_strchr(str, 0));
// 	printf("%s yeah", strchr(str, 0));
// }
