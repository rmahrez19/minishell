/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:01:08 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/12 00:58:17 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static int	checkchar(char c, char const *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*tab;

	start = 0;
	while (s1[start] && checkchar(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && checkchar(s1[end - 1], set))
		end--;
	len = end - start;
	tab = (char *)malloc(sizeof(char) * (len + 1));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s1 + start, len + 1);
	return (tab);
}
// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*s1;

// 	s1 = "lorem \n ipsum \t dolor \n sit \t amet";
// 	printf("%s", ft_strtrim(s1, " "));
// }
