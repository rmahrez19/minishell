/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:02:11 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:16:01 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (1);
	if (str[i] == '=' && str[++i])
		return (0);
	return (1);
}

void	print_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_tab[i])
	{
		if (data->env_tab[i][0] && has_value(data->env_tab[i]))
			ft_putendl_fd(data->env_tab[i], 1);
		i++;
	}
}

int	ft_env(t_token *lst, t_data *data)
{
	t_token	*temp;

	temp = lst;
	while (temp)
	{
		if (!ft_strcmp(temp->arg, "env"))
			temp = temp->next;
		else if (!ft_strncmp(temp->arg, "./", 2))
			return (print_env_error(temp->arg, 126));
		else
			return (print_env_error(temp->arg, 127));
	}
	if (!ft_strncmp(lst->arg, "env", 4))
	{
		print_env(data);
		return (0);
	}
	return (1);
}

int	ft_env_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->env_tab && data->env_tab[i])
	{
		if (ft_strchr(data->env_tab[i], '='))
		{
			ft_putendl_fd(data->env_tab[i], 1);
		}
		i++;
	}
	return (0);
}
