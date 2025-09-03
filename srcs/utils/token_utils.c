/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:50:05 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 14:47:55 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '(' || c == ')');
}

int	is_full_operator(const char *str, int i)
{
	if ((str[i] == '&' && str[i + 1] == '&')
		|| (str[i] == '|' && str[i + 1] == '|'))
		return (2);
	return (1);
}

int	is_event_in_token(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '!')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(arg + i, 2);
			ft_putstr_fd(": event not found\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_bad_tokens(t_token *lst)
{
	if (is_only_pipe(lst->arg) && lstsize(lst) == 1)
		return (print_unexpected(lst->arg), 1);
	if (is_only_and(lst->arg) && lstsize(lst) == 1)
		return (print_unexpected("&&"), 1);
	if (is_only_point_virgule(lst->arg) && lstsize(lst) == 1)
		return (print_unexpected(";;"), 1);
	return (0);
}

void	put_char_backslash(t_builtin *s, char *arg)
{
	s->i++;
	ft_putchar_fd(arg[s->i++], 1);
}
