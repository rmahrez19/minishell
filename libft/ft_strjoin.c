/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:03:27 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:48:19 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*tab;
	size_t		i;
	int			y;

	i = 0;
	y = 0;
	tab = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tab == NULL)
		return (tab);
	while (i < ft_strlen(s1))
	{
		tab[y] = s1[i];
		i++;
		y++;
	}
	i = 0;
	while (i < ft_strlen(s2))
		tab[y++] = s2[i++];
	tab[y] = '\0';
	return (tab);
}

// #include <stdio.h>
// int main (void)
// {
// 	char *s1 = "Hello ";
// 	char *s2 = "les coupains!!";
// 	printf("%s", ft_strjoin(s1, s2));
// }