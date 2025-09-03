/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loubriottet <loubriottet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:17:02 by lobriott          #+#    #+#             */
/*   Updated: 2024/11/12 03:54:15 by loubriottet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c == 0)
		return (0);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//#include <stdio.h>
//int main (void)
//{
//    int i = 49;
//    printf("%d", ft_isdigit(i));
//}
