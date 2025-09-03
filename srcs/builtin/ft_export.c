/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:50:00 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/02 22:04:37 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	print_unvalid_args(int i, char *arg)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		put_error_export(arg);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	return (0);
}

static int	validate_and_export_args(char **args, t_data *data)
{
	t_builtin	s;

	s.i = 0;
	s.error = 0;
	s.add_equal = 0;
	remove_quotes_from_arg_tab(args);
	if (!args || !args[0])
		return (0);
	while (args[s.i])
		replace_tildes(args[s.i++]);
	s.i = 0;
	while (args[s.i])
	{
		if (!ft_strcmp(args[s.i], "=") || !ft_strcmp(args[s.i], "=~"))
			s.add_equal = 1;
		if (args[s.i][0] != 126 && !is_valid_key(args[s.i])
			&& args[s.i][0] != '-' && args[s.i][ft_strlen(args[s.i])] != '"')
			s.error = print_unvalid_args(1, args[s.i]);
		else if (!is_valid_key(args[s.i]) && args[s.i][0] == '-')
			s.error = print_option_issues(args[s.i]);
		else
			update_env(&data->env_tab, args[s.i]);
		s.i++;
	}
	return (s.error);
}

int	ft_export(t_token *lst, t_data *data)
{
	char	**args;
	int		error;

	if (lstsize(lst) == 1)
		return (print_export_sorted(data->env_tab), 0);
	if (check_token_validity(lst))
		return (1);
	if (lstsize(lst) <= 2 && !ft_strcmp(lst->next->arg, ""))
		return (print_export_sorted(data->env_tab), 0);
	args = build_args(lst, data);
	if (!args)
		return (free_tab(args), 0);
	error = validate_and_export_args(args, data);
	free_tab(args);
	return (error);
}

int	launch_export_array(char **args, t_data *data, t_builtin *s)
{
	if (is_valid_option(args[1]))
		return (2);
	s->i = 1;
	while (args[s->i])
	{
		if (args[s->i] && !is_valid_key(args[s->i]))
			return (print_export_error(args[s->i], 2, data->env_tab), 1);
		else if (ft_strchr(args[s->i], '='))
		{
			s->eq_index = ft_strchr(args[s->i], '=') - args[s->i];
			s->key = ft_substr(args[s->i], 0, s->eq_index);
			s->val = expand_if_needed(args[s->i++] + s->eq_index + 1, data);
			s->tmp = ft_strjoin(s->key, "=");
			s->joined = ft_strjoin(s->tmp, s->val);
			update_env(&data->env_tab, s->joined);
			free_export_variables(s);
		}
		s->i++;
	}
	return (0);
}

int	ft_export_pipe(char **args, t_data *data)
{
	t_builtin	s;

	if (!args[1])
		return (print_export_sorted(data->env_tab), 0);
	if (args[1][0] == '$' && !env_var_exists(args[1], data->env_tab))
		return (print_export_sorted(data->env_tab), 0);
	return (launch_export_array(args, data, &s));
}
