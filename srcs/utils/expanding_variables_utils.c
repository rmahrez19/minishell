/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_variables_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:49:41 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:11:48 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	expand_variables_util(char *line, t_exec *s)
{
	if (!line)
		return (1);
	s->result = ft_strdup("");
	if (!s->result)
		return (1);
	s->i = 0;
	return (0);
}

void	making_temp_ptr(char *line, t_exec *s, t_data *data)
{
	s->i++;
	s->j = 0;
	while ((ft_isalnum(line[s->i]) || line[s->i] == '_') && s->j < 255)
		s->var_name[s->j++] = line[s->i++];
	s->var_name[s->j] = '\0';
	s->full_var[0] = '$';
	ft_strlcpy(s->full_var + 1, s->var_name, 257);
	s->var_value = find_env(s->full_var, data->env_tab);
	if (!s->var_value)
		s->var_value = "";
	s->temp = ft_strjoin(s->result, s->var_value);
	free(s->result);
}

void	manage_question_mark2(t_exec *s, t_data *data)
{
	s->temp = adding_result(s->result, ft_itoa(data->exit_code), 1);
	s->i += 2;
}

void	simple_add(t_exec *s, char *line)
{
	s->temp = adding_result(s->result, from_char_to_str(line[s->i++], 0), 1);
}

int	expand_step(char *line, t_data *data, t_exec *s)
{
	if (line[s->i] == '$' && line[s->i + 1] == '?')
	{
		manage_question_mark2(s, data);
		if (!s->temp)
			return (-1);
	}
	else if (line[s->i] == '$' && line[s->i + 1] == '$')
	{
		if (add_pid_from_proc(s))
			return (-1);
	}
	else if (line[s->i] == '$' && line[s->i + 1] && (ft_isalnum(line[s->i + 1])
			|| line[s->i + 1] == '_'))
		making_temp_ptr(line, s, data);
	else if ((line[s->i] == '$' && line[s->i + 1] == '\'') || (line[s->i] == '$'
			&& line[s->i + 1] == '\"'))
		manage_quote_and_dollar(s, line);
	else
		simple_add(s, line);
	s->result = s->temp;
	return (0);
}
