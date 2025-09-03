/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 00:09:19 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/18 14:04:29 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	lennum(unsigned int i)
{
	int	len;

	len = 0;
	if (i == 0)
		return (1);
	while (i > 0)
	{
		i /= 10;
		len++;
	}
	return (len);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = lennum(n);
	if (n >= 10)
	{
		ft_putunsigned(n / 10);
		ft_putchar((n % 10) + '0');
	}
	else
		ft_putchar(n + '0');
	return (count);
}
