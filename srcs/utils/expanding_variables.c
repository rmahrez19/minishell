/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_variables.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:58:15 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:12:49 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*puting_unquoted(char *dest, char *start_ptr, int i, char c)
{
	char	*result;
	int		j;
	char	*ptr;

	j = i;
	i = 2;
	while (start_ptr[i] && start_ptr[i] != c)
		i++;
	result = malloc(i - 2 + 1);
	if (!result)
		return (free(dest), NULL);
	i = j + 2;
	j = 0;
	while (start_ptr[i] && start_ptr[i] != c)
		result[j++] = start_ptr[i++];
	result[j] = '\0';
	ptr = ft_strjoin(dest, result);
	free(dest);
	free(result);
	return (ptr);
}

void	manage_quote_and_dollar(t_exec *s, char *line)
{
	s->temp = puting_unquoted(s->result, line, s->i, line[s->i + 1]);
	s->i = move_i(s->i, line, line[s->i]);
}

int	add_uid(t_exec *s, t_data *data)
{
	s->line = get_env_value("UID", data);
	if (!s->line)
		return (free(s->temp), 1);
	s->temp = adding_result(s->result, s->line, 0);
	s->i += 2;
	return (0);
}

char	*launch_expanding(char *line, t_data *data, t_exec *s)
{
	while (line[s->i])
	{
		if (expand_step(line, data, s) < 0)
			return (free(s->result), NULL);
	}
	if (s->result[0] == '\'')
		s->quote = 1;
	else
		s->quote = 0;
	s->temp = remove_quotes(s->result, s);
	if (s->flags == 1)
		return (s->result);
	free(s->result);
	return (s->temp);
}

char	*expand_variables(char *line, t_data *data)
{
	t_exec	s;

	if (expand_variables_util(line, &s))
		return (NULL);
	return (launch_expanding(line, data, &s));
}
