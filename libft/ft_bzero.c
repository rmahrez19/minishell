/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:10:52 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/12 03:42:02 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}

// #include <stdio.h>
// int main (void)
// {
//     size_t n = 5;
//     char c[] = "hello les boys";
//     printf("ma string %s \n", c);
//     ft_bzero(c, n);
//     int i = 0;
//     while (c[i] == 0)
//         i++;
//     printf("apres la fonction =>");
//         printf("%s", c + i);    
// }
