/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:18:56 by ramahrez          #+#    #+#             */
/*   Updated: 2025/03/06 15:48:28 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putlstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_put_point(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int nb)
{
	long int	n;
	int			len;

	len = 0;
	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
		len++;
	}
	if (n > 9)
	{
		len += ft_putnbr(n / 10);
		len += ft_putnbr(n % 10);
	}
	if (n < 10)
	{
		len += ft_putchar(n + '0');
	}
	return (len);
}
