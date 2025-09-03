/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_dollarutils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 18:05:22 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 17:23:19 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_valid_varname_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '*');
}

static int	handle_special_dollar(char *ptr, t_data *data, int *i)
{
	char	*pid_str;

	if (ptr[1] == '?')
	{
		ft_printf("%d", data->exit_code);
		*i += 2;
		return (1);
	}
	if (ptr[1] == '$')
	{
		pid_str = ft_itoa(getpid());
		if (pid_str)
		{
			ft_putstr_fd(pid_str, 1);
			free(pid_str);
		}
		*i += 2;
		return (1);
	}
	return (0);
}

static int	handle_digit_or_quote(char *ptr, int *i)
{
	int	j;

	if (ft_isdigit(ptr[1]))
	{
		j = 2;
		*i += 2;
		while (ft_isdigit(ptr[j]))
		{
			j++;
			*i += 1;
		}
		return (1);
	}
	if (ptr[1] == '"' || ptr[1] == '\'')
	{
		*i += 1;
		return (1);
	}
	if (!ptr[1] || (!ft_isalpha(ptr[1]) && ptr[1] != '_'))
	{
		write(1, "$", 1);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	handle_env_var(char *ptr, t_data *data, int *i)
{
	char	var_name[256];
	char	with_dollar[257];
	char	*value;
	int		j;

	j = 0;
	while (ptr[1 + j] && is_valid_varname_char(ptr[1 + j]) && j < 255)
	{
		var_name[j] = ptr[1 + j];
		j++;
	}
	var_name[j] = '\0';
	with_dollar[0] = '$';
	ft_strlcpy(with_dollar + 1, var_name, 256);
	value = find_env(with_dollar, data->env_tab);
	if (value)
		ft_putstr_fd(value, 1);
	*i += 1 + j;
	return (1);
}

int	handle_dollar_case(char *ptr, t_data *data, int *i)
{
	int	ret;

	ret = handle_special_dollar(ptr, data, i);
	if (ret)
		return (ret);
	ret = handle_digit_or_quote(ptr, i);
	if (ret)
		return (ret);
	return (handle_env_var(ptr, data, i));
}
