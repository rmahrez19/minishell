/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:33:54 by ramahrez          #+#    #+#             */
/*   Updated: 2025/04/13 15:37:26 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft.h"

// # define secur "cspdiuxX%"
// # define BASE_DEC "0123456789"
// # define BASE_HEX "0123456789abcdef"
// # define BASE_HEX_UPP "0123456789ABCDEF"

int		ft_putlstr(char *str);
int		ft_put_point(char c);
int		ft_putnbr(int nb);
int		ft_nb(int nb, int base);
int		ft_putadr(void *ptr);
int		ft_putlunbr_base(unsigned int nb, char *base);
int		ft_putchar(char c);
int		ft_printf(const char *format, ...);

void	ft_error(void);
void	error_arg(void);
// void	ft_putstr(char *str);
void	ft_pri(char *format, void *arg, int nb_args, int *i);

#endif