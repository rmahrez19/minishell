/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:07:52 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/23 16:32:58 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\\')
			write(fd, &s[i++], 1);
		else
			i++;
	}
}

// int main (void)
// {
// 	ft_putstr_fd("hello", 1);
// }