/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 23:59:32 by hectordavro       #+#    #+#             */
/*   Updated: 2025/07/11 23:47:59 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_quotes_closed(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == SINGLE_QUOTE || line[i] == DOUBLE_QUOTE)
		{
			quote = line[i++];
			while (line[i] && line[i] != quote)
				i++;
			if (!line[i])
				return (0);
		}
		if (line[i])
			i++;
	}
	return (1);
}
