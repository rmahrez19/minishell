/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 11:23:05 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 17:55:28 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_dollar_in_quote(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' && str[i + 1] == '$')
		return (1);
	return (0);
}

int	print_between_quote(char *arg, int start, char quote_type, t_data *data)
{
	int	i;

	i = start + 1;
	while (arg[i] && arg[i] != quote_type)
	{
		if (quote_type == '"' && arg[i] == '$')
			handle_dollar_case(&arg[i], data, &i);
		else
		{
			ft_putchar_fd(arg[i], 1);
			i++;
		}
	}
	if (arg[i] == quote_type)
		i++;
	return (i - start - 1);
}

int	only_ws(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= 32)
			i++;
		else
			return (0);
	}
	if (!str[i])
		return (1);
	return (2);
}

void	echo_token_arg_util(char *arg, int i)
{
	if (arg[i] == 126)
		ft_putchar(34);
	else
		write(1, &arg[i], 1);
}

void	put_expanded(t_builtin *s)
{
	if (s->expanded[0] == '$' && ft_isalnum(s->expanded[1]))
		ft_putstr_fd(s->expanded + 1, 1);
	else
		ft_putstr_fd(s->expanded, 1);
}
