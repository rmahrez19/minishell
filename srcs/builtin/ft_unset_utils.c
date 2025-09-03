/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:47:33 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/02 17:24:56 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_unset_error(char *str, int type, char **envp)
{
	char	*expanded;

	if (type == 1)
	{
		expanded = find_env(str, envp);
		ft_putstr_fd("minishell: unset: ' -", 2);
		if (expanded)
			write(2, &expanded[1], 1);
		else if (str[1])
			write(2, &str[1], 1);
		ft_putendl_fd("': invalid option", 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	else if (type == 3)
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(str + 1, 2);
		ft_putendl_fd(": invalid parameter name", 2);
	}
	return (1);
}

int	is_valid_identifier(char *str, t_data *data, int *ptr)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (str[0] == '-')
		return (*ptr = 2, data->exit_code = 1,
			print_unset_error(str, 1, data->env_tab));
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (*ptr = 1, data->exit_code = 1,
			print_unset_error(str, 2, data->env_tab));
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (*ptr = 1, data->exit_code = 1,
				print_unset_error(str, 2, data->env_tab));
		i++;
	}
	return (1);
}

int	handle_unset_error(char *arg)
{
	if (!arg[0] || !ft_strcmp("\"\"", arg))
	{
		ft_putstr_fd("minishell: unset: `': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

void	remove_env_var(char *var_name, int dollar, t_data *data)
{
	int	i;
	int	y;
	int	len;

	len = ft_strlen(var_name);
	i = 0;
	while (data->env_tab && data->env_tab[i])
	{
		if (!dollar && !ft_strncmp(var_name, data->env_tab[i], len)
			&& data->env_tab[i][len] == '=')
		{
			data->env_tab[i][0] = '\0';
			break ;
		}
		else if (dollar && !ft_strncmp(var_name, data->env_tab[i], len))
		{
			y = 0;
			while (data->env_tab[i][y] && data->env_tab[i][y] != '=')
				y++;
			if (data->env_tab[i][y + 1])
				data->env_tab[i][y + 1] = '\0';
		}
		i++;
	}
	free(var_name);
}
