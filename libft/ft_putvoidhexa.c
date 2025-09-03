/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putvoidhexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:26:48 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/18 18:26:50 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

static void	puthexa(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	while (i >= 0)
	{
		write(1, &str[i], 1);
		i--;
	}
}

int	ft_putvoidhexa(void *adress, char *base)
{
	int					i;
	char				str[18];
	unsigned long long	nb;

	if (adress == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	nb = (unsigned long long)adress;
	i = 0;
	while (nb > 0)
	{
		str[i] = base[nb % 16];
		nb = nb / 16;
		i++;
	}
	str[i++] = 'x';
	str[i++] = '0';
	str[i++] = '\0';
	puthexa(str);
	return (i - 1);
}
// #include <stdio.h>
// int main (void)
// {
//     void *ptr = "hello";
//     size_t a = (size_t)ptr;
//     nbhexa(a, "0123456789abcdef");
//     printf(" %zu" ,a);
// }
