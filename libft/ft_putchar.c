/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:13:33 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/11 23:14:24 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

int	ft_putchar(char c)
{
	char	*cc;

	cc = malloc(sizeof(char) * 2);
	if (cc == NULL)
		return (0);
	cc[0] = c;
	cc[1] = '\0';
	write(1, &cc[0], 1);
	free(cc);
	return (1);
}
