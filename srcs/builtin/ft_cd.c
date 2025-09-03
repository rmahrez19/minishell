/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:30:00 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 19:43:44 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_go_home(t_data *data)
{
	char	*home;

	home = find_env("$HOME", data->env_tab);
	if (!home && !env_var_exists("$HOME", data->env_tab))
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (1);
	}
	else if (chdir(home) == -1)
		return (0);
	return (update_pwd(data));
}

char	*expand_variable_path(char *arg, t_data *data)
{
	t_cd	s;

	if (!arg || arg[0] != '$')
		return (NULL);
	s.i = 1;
	s.j = 0;
	while ((ft_isalnum(arg[s.i]) || arg[s.i] == '_') && s.j < 255)
		s.var_name[s.j++] = arg[s.i++];
	s.var_name[s.j] = '\0';
	if (s.j == 0)
		return (NULL);
	s.full_var[0] = '$';
	ft_strlcpy(s.full_var + 1, s.var_name, 257);
	s.env_val = find_env(s.full_var, data->env_tab);
	if (!s.env_val)
		return (NULL);
	if (arg[s.i] == '\0')
		return (ft_strdup(s.env_val));
	s.result = ft_strjoin(s.env_val, arg + s.i);
	return (s.result);
}

static int	cd_go_to_path(char *path, t_data *data)
{
	t_cd	s;

	if (path[0] == '-' && ft_strlen(path) > 2)
		return (print_option_issues(path));
	s.expanded = expand_variable_path(path, data);
	if (s.expanded)
		return (manage_expanded(data, s.expanded, path));
	s.temp = remove_quotes_cd(path);
	if (!s.temp)
	{
		s.temp = expand_variables(path, data);
		if (s.temp)
		{
			if (chdir(s.temp) == -1)
				return (prefix(), perror(s.temp), free(s.temp), 1);
			free(s.temp);
			return (update_pwd(data));
		}
		if (chdir(path) == -1)
			return (prefix(), perror(path), 1);
		return (update_pwd(data));
	}
	else if (chdir(s.temp) == -1)
		return (prefix(), perror(s.temp), free(s.temp), 1);
	return (free(s.temp), update_pwd(data));
}

int	ft_cd(t_token *lst, t_data *data)
{
	int	ret;

	if (cd_too_many_args(lst))
	{
		data->exit_code = 1;
		return (1);
	}
	if (!lst->next || !lst->next->arg)
		ret = cd_home_case(data);
	else if (!ft_strcmp(lst->next->arg, "$HOME")
		|| !ft_strcmp(lst->next->arg, "~"))
		ret = cd_go_home(data);
	else if (!ft_strncmp(lst->next->arg, "-", 2))
		ret = cd_dash_case(data);
	else
		ret = cd_go_to_path(lst->next->arg, data);
	data->exit_code = ret;
	return (ret);
}

int	ft_cd_pipe(char **args, t_data *data)
{
	int	ret;

	if (!args[1])
		ret = cd_home_case(data);
	else if (!ft_strncmp(args[1], "-", 2))
		ret = cd_dash_case(data);
	else
		ret = cd_go_to_path(args[1], data);
	data->exit_code = ret;
	return (ret);
}
