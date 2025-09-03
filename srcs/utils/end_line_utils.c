/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_line_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:17:00 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 19:44:48 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_good_char(char c, int mode)
{
	if (mode == 1)
	{
		if (c && c > 32 && !is_operator_char(c)
			&& c != '\'' && c != '"' && c != '>' && c != '<')
			return (1);
	}
	else if (mode == 2)
	{
		if (c && c != '>' && c != '<' && c > 32 && !is_operator_char(c)
			&& c != '\'' && c != '"')
			return (1);
	}
	else if (mode == 3)
	{
		if (c && !isspace(c) && c != '|' && c != '>' && c != '<')
			return (1);
	}
	return (0);
}

static char	*removing_the_quotes(char *str, t_utils *s)
{
	while (str[s->i])
	{
		if ((str[s->i] == '\'' && !s->is_inside)
			|| (str[s->i] == '"' && !s->is_inside))
		{
			s->is_inside = str[s->i];
			s->i++;
		}
		else if (str[s->i] == s->is_inside)
		{
			s->is_inside = 0;
			s->i++;
		}
		else if (str[s->i])
		{
			s->res[s->j] = str[s->i];
			s->j++;
			s->i++;
		}
	}
	s->res[s->j] = '\0';
	return (s->res);
}

char	*remove_quotes(char *str, t_exec *st)
{
	t_utils	s;

	s.is_inside = 0;
	s.i = 0;
	s.j = 0;
	while (str[s.i])
	{
		st->flags = 0;
		if (str[s.i] == '=')
		{
			st->flags = 1;
			return (str);
		}
		if (str[s.i] == '\'')
			break ;
		s.i++;
	}
	s.i = 0;
	s.res = malloc(ft_strlen(str) + 1);
	if (!s.res)
		return (NULL);
	else
		return (removing_the_quotes(str, &s));
}

char	*remove_quotes_cd(char *str)
{
	t_utils	s;

	s.is_inside = 0;
	s.i = 0;
	s.j = 0;
	s.res = malloc(ft_strlen(str) + 1);
	if (!s.res)
		return (NULL);
	else
		return (removing_the_quotes(str, &s));
}
