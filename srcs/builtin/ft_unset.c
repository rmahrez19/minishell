/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:37:54 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/04 09:39:32 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_and_get_var(char *arg, t_data *data, int *dollar)
{
	char	*expanded;
	char	*result;

	expanded = expand_variables(arg, data);
	if (!expanded)
		return (NULL);
	if (expanded[0] == '$')
	{
		*dollar = 1;
		if (!find_line(expanded, data->env_tab))
		{
			print_unset_error(expanded, 3, data->env_tab);
			free(expanded);
			return (NULL);
		}
		result = ft_strdup(expanded + 1);
		free(expanded);
		return (result);
	}
	*dollar = 0;
	return (expanded);
}

int	ft_unset_launch(t_data *data, t_builtin *s)
{
	while (s->temp)
	{
		if (is_event_in_token(s->temp->arg))
			return (1);
		if (handle_unset_error(s->temp->arg))
		{
			s->error = 1;
			s->temp = s->temp->next;
			continue ;
		}
		s->var_name = expand_and_get_var(s->temp->arg, data, &s->dollar);
		if (!is_valid_identifier(s->var_name, data, &s->error))
			free(s->var_name);
		if (!s->var_name)
		{
			s->temp = s->temp->next;
			continue ;
		}
		remove_env_var(s->var_name, s->dollar, data);
		s->temp = s->temp->next;
	}
	return (s->error);
}

int	ft_unset(t_token *lst, t_data *data)
{
	t_builtin	s;

	s.error = 0;
	s.temp = lst->next;
	return (ft_unset_launch(data, &s));
}

int	ft_unset_pipe_launch(char **args, t_data *data, t_builtin *s)
{
	while (args[s->i])
	{
		if (handle_unset_error(args[s->i]))
		{
			s->error = 1;
			s->i++;
			continue ;
		}
		s->var_name = expand_and_get_var(args[s->i], data, &s->dollar);
		if (!is_valid_identifier(s->var_name, data, &s->error))
			free(s->var_name);
		if (!s->var_name)
		{
			s->temp = s->temp->next;
			continue ;
		}
		remove_env_var(s->var_name, s->dollar, data);
		s->i++;
	}
	return (s->error);
}

int	ft_unset_pipe(char **args, t_data *data)
{
	t_builtin	s;

	s.i = 1;
	s.error = 0;
	if (!args || !args[1])
		return (0);
	return (ft_unset_pipe_launch(args, data, &s));
}
