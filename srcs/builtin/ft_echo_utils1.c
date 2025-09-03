/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:20:51 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/26 17:43:31 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_simple_quote(char *line)
{
	if (!line)
		return (0);
	if (line[0] == '\'' && line[ft_strlen(line) - 1]
		== '\'' && ft_strlen(line) >= 2)
		return (1);
	return (0);
}

int	check_double_quote(char *line)
{
	if (!line)
		return (0);
	if (line[0] == '\"' && line[ft_strlen(line) - 1]
		== '\"' && ft_strlen(line) >= 2)
		return (ft_strlen(line) - 1);
	return (0);
}

int	putstr_without_quote(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!(i == 0 && line[i] == '\'')
			&& !(i == ft_strlen(line) - 1 && line[i] == '\'')
			&& line[i] != '\\' && line[i] != '\"')
			write(1, &line[i], 1);
		i++;
	}
	return (i);
}

void	putstr_with_escaping(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\\' && s[i + 1])
			i++;
		if (s[i])
			write(1, &s[i], 1);
		i++;
	}
}
