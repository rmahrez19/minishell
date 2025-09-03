/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:01:59 by ramahrez          #+#    #+#             */
/*   Updated: 2025/08/12 17:48:16 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	skip_quoted(char *line, int i, int *j)
{
	char	q;

	q = line[i + *j];
	(*j)++;
	while (line[i + *j] && line[i + *j] != q)
		(*j)++;
	if (line[i + *j] == q)
		(*j)++;
}

char	*ft_replace_line(char *line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_malloc(strlen(line) + 1);
	if (!res)
		return (NULL);
	while (line[i + j])
	{
		if (line[i + j] == '\'' || line[i + j] == '\"')
			skip_quoted(line, i, &j);
		res[i] = line[i + j];
		if (line[i + j])
			i++;
	}
	res[i] = '\0';
	return (res);
}
