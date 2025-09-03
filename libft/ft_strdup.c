/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:37:25 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 00:48:10 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstring;
	size_t	i;

	i = 0;
	newstring = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (newstring == NULL)
		return (newstring);
	while (i < ft_strlen(s1))
	{
		newstring[i] = s1[i];
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
// #include <string.h>
// #include <stdio.h>
// int main (void)
// {
// char *str = "hello";
// printf("%s \n", ft_strdup(str));
// printf("%s", strdup(str));
// }