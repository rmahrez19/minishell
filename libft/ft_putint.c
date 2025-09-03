/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:18:29 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/18 14:04:16 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_putcharvoid(char c)
{
	write(1, &c, 1);
	return (1);
}

static int	lennum(long int i)
{
	int				a;
	unsigned int	u;

	a = 0;
	if (i < 0)
	{
		a++;
		u = -i;
	}
	else
		u = i;
	if (u == 0)
		return (1);
	while (u > 0)
	{
		u = u / 10;
		a++;
	}
	return (a);
}

int	ft_putint(int i)
{
	int	nb;

	nb = i;
	if (i == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (i < 0)
	{
		write(1, "-", 1);
		i = -i;
	}
	if (i < 10)
		ft_putcharvoid(i + 48);
	if (i >= 10)
	{
		ft_putint(i / 10);
		ft_putint(i % 10);
	}
	return (lennum(nb));
}

// #include <stdio.h>
// int main (void)
// {
// 	int i = 12;

// 	printf("%d \n %i", i , i);
// }