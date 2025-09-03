/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:12:52 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/18 14:01:03 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	argument;

	va_start(argument, format);
	i = 0;
	count = 0;
	if (format == NULL)
		return (-1);
	while (format[i])
	{
		if (format[i] != '%')
			write(1, &format[i], 1);
		if (format[i] == '%')
		{
			if (ft_iscspdiux(format[i++]) == 1)
				count += ft_putft(format[i], argument) - 2;
			else
				count--;
		}
		i++;
	}
	va_end(argument);
	return (i + count);
}

// #include <stdio.h>

// #include "ft_printf.h"

// int main(void)
// {
// 	int i = ft_printf(" %p %p ", 0, 0);
//     int j = printf(" %p %p ", 0, 0);

// 	printf(" \n ma ft = %d \n vraie ft = %d", i, j);
//     return (0);
// }
