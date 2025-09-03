/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_remove_ws.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:15:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/04/02 18:20:28 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

static bool	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	ft_count_words(const char *str)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (str[i] && !is_whitespace(str[i]))
		{
			word++;
			while (str[i] && !is_whitespace(str[i]))
				i++;
		}
	}
	return (word);
}

static char	*ft_word(const char *str, int *i)
{
	char	*s;
	int		k;
	int		start;

	start = *i;
	k = 0;
	while (str[*i] && !is_whitespace(str[*i]))
	{
		(*i)++;
		k++;
	}
	s = malloc(sizeof(char) * (k + 1));
	if (!s)
		return (NULL);
	k = 0;
	while (start < *i)
		s[k++] = str[start++];
	s[k] = '\0';
	while (str[*i] && is_whitespace(str[*i]))
		(*i)++;
	return (s);
}

char	**ft_split_whitespace(const char *str)
{
	int		i;
	int		j;
	int		wrd;
	char	**s;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	wrd = ft_count_words(str);
	s = malloc(sizeof(char *) * (wrd + 1));
	if (!s)
		return (NULL);
	while (str[i] && is_whitespace(str[i]))
		i++;
	while (j < wrd && str[i])
		s[j++] = ft_word(str, &i);
	s[j] = NULL;
	return (s);
}
