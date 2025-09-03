/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:11:23 by ramahrez          #+#    #+#             */
/*   Updated: 2025/02/27 18:32:44 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putlunbr_base(unsigned int n, char *base)
{
	int				len;
	unsigned int	len_base;

	if (!n)
		return (ft_putchar('0'));
	len_base = ft_strlen(base);
	len = 0;
	if (n >= len_base)
		len += ft_putlunbr_base(n / len_base, base);
	len += write(1, &base[n % len_base], 1);
	return (len);
}

int	ft_putadr(void *ptr)
{
	char				*hex;
	int					len;
	unsigned long long	addr;

	if (!ptr)
		return (ft_putlstr("(nil)"));
	addr = (unsigned long long)ptr;
	hex = "0123456789abcdef";
	len = 0;
	if (addr >= 16)
		len += ft_putadr((void *)(addr / 16));
	if (len == 0)
		len += ft_putlstr("0x");
	len += write(1, &hex[addr % 16], 1);
	return (len);
}
