/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:06:14 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:16:58 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_values_export(t_builtin *s, t_data *data, char *str, int i)
{
	if (i == 1)
	{
		s->tmp = ft_substr(str, s->start, s->i - s->start);
		s->res = ft_strjoin_free(s->res, get_env_value(s->tmp, data));
	}
	if (i == 2)
	{
		s->tmp = ft_substr(str, s->start, s->i - s->start);
		s->res = ft_strjoin_free(s->res, s->tmp);
	}
}

void	incremente_i_j(t_builtin *s)
{
	s->i += 1;
	s->j += 1;
}

void	quotes_from_arg_tab(char **tab, t_builtin *s)
{
	while (tab[s->i])
	{
		s->j = 0;
		while (tab[s->i][s->j])
		{
			if ((tab[s->i][s->j] == '"' && !s->is_inside)
				|| (tab[s->i][s->j] == '\'' && !s->is_inside))
			{
				s->is_inside = tab[s->i][s->j];
				tab[s->i][s->j] = 126;
			}
			else if ((tab[s->i][s->j] == '"' && s->is_inside == tab[s->i][s->j])
					|| (tab[s->i][s->j] == '\''
					&& s->is_inside == tab[s->i][s->j]))
			{
				s->is_inside = 0;
				tab[s->i][s->j] = 126;
			}
			s->j++;
		}
		s->i++;
	}
}

void	remove_quotes_from_arg_tab(char **tab)
{
	t_builtin	s;

	s.i = 0;
	s.is_inside = 0;
	quotes_from_arg_tab(tab, &s);
}

void	replace_tildes(char *str)
{
	int	i;
	int	j;
	int	index;

	i = 0;
	(void)index;
	while (str[i])
	{
		if (str[i] == 126)
		{
			index = i;
			j = i + 1;
			while (str[j])
			{
				str[i] = str[j];
				i++;
				j++;
			}
			str[i] = '\0';
			if (index)
				i = index;
			index = 0;
		}
		i++;
	}
}
