/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:19:03 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/13 23:14:25 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

static int	intlen(int n, int sign)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (11);
	if (n == 2147483647)
		return (10);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	if (sign == -1)
		len++;
	return (len);
}

static void	fill_str(char *result, unsigned int i, int len, int sign)
{
	result[len--] = '\0';
	if (i == 0)
	{
		result[0] = '0';
		result[1] = '\0';
		return ;
	}
	while (i > 0)
	{
		result[len--] = '0' + (i % 10);
		i /= 10;
	}
	if (sign == -1)
		result[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*result;
	int				sign;
	int				len;
	unsigned int	nomb;

	if (n < 0)
	{
		sign = -1;
		nomb = -n;
	}
	else
	{
		nomb = n;
		sign = 1;
	}
	len = intlen(nomb, sign);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	fill_str(result, nomb, len, sign);
	return (result);
}

// #include <stdio.h>
// int main (void)
// {
// 	int i = -1 ;
// 	char *str = ft_itoa(i);
// 	printf("%s", str);
// 	free (str);
// }
