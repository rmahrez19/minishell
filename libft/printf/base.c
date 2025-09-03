/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:32:26 by ramahrez          #+#    #+#             */
/*   Updated: 2024/11/21 16:35:01 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"

int	ft_tri(char c, va_list ap)
{
	if (c == 'c')
	{
		ft_put_point(va_arg(ap, int));
		return (1);
	}
	if (c == 's')
		return (ft_putlstr(va_arg(ap, char *)));
	if (c == 'p')
		return (ft_putadr(va_arg(ap, void *)));
	if ((c == 'd') || (c == 'i'))
		return (ft_putnbr(va_arg(ap, int)));
	if (c == 'u')
		return (ft_putlunbr_base(va_arg(ap, unsigned int), "0123456789"));
	if (c == 'x')
		return (ft_putlunbr_base(va_arg(ap, unsigned int), "0123456789abcdef"));
	if (c == 'X')
		return (ft_putlunbr_base(va_arg(ap, unsigned int), "0123456789ABCDEF"));
	if (c == '%')
	{
		ft_putchar('%');
		return (1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!format)
		return (-1);
	va_start (ap, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_tri(format[i + 1], ap);
			i++;
		}
		else
		{
			len ++;
			ft_putchar(format[i]);
		}
		i++;
	}
	va_end(ap);
	return (len);
}
