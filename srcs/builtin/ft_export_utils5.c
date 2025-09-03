/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:42:37 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 21:08:25 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	set_ptr_value(t_token *lst, t_builtin *s)
{
	s->temp = lst->next;
	s->ptr = NULL;
	s->args = malloc(sizeof(char *) * (count_args(lst) + 1));
	if (!s->args)
		return (1);
	return (0);
}

char	*remove_quotes_and_concatenate(const char *str)
{
	int		i;
	int		k;
	char	*res;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			res[k++] = str[i];
		i++;
	}
	res[k] = '\0';
	return (res);
}

int	print_export_error(char *str, int type, char **envp)
{
	char	*expanded;

	if (type == 1)
	{
		expanded = find_env(str, envp);
		if (!expanded)
			return (0);
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(expanded, 2);
		ft_putendl_fd("': invalid option", 2);
		free(expanded);
	}
	else if (type == 2)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	else if (type == 3)
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(str + 1, 2);
		ft_putendl_fd(": invalid parameter name", 2);
	}
	return (1);
}

char	*expand_if_needed(char *str, t_data *data)
{
	t_builtin	s;

	s.res = ft_strdup("");
	s.i = 0;
	if (!ft_strcmp(str, "?"))
		return (ft_strjoin_free(s.res, ft_itoa(data->exit_code)), s.res);
	while (str[s.i])
	{
		if (str[s.i] == '$')
		{
			s.start = ++s.i;
			while (str[s.i] && (ft_isalnum(str[s.i]) || str[s.i] == '_'))
				s.i++;
			set_values_export(&s, data, str, 1);
			free(s.tmp);
		}
		else
		{
			s.start = s.i;
			while (str[s.i] && str[s.i] != '$')
				s.i++;
			set_values_export(&s, data, str, 2);
		}
	}
	return (s.res);
}

char	**build_args(t_token *lst, t_data *data)
{
	t_builtin	s;

	if (set_ptr_value(lst, &s) == 1)
		return (NULL);
	s.i = 0;
	while (s.temp)
	{
		s.expanded = expand_variables(s.temp->arg, data);
		if (s.ptr)
			s.args[s.i] = ft_strjoin_free(s.args[s.i], s.expanded);
		else
			s.args[s.i] = ft_strdup(s.expanded);
		if (s.temp->colle_next)
			s.ptr = s.args[s.i];
		else
		{
			s.ptr = NULL;
			s.i++;
			s.args[s.i] = NULL;
		}
		free(s.expanded);
		s.temp = s.temp->next;
	}
	return (s.args);
}
