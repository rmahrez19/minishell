/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:39:43 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/03 16:59:18 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_verif_exit(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (EXIT[i])
	{
		if (EXIT[i] != str[i])
			return ;
		i++;
	}
	if (str[i] != 0)
		return ;
	if (data->env_tab)
		free_tab(data->env_tab);
	rl_clear_history();
	ft_free();
	data->exit_code = 0;
	exit(data->exit_code);
}

int	check_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			break ;
		if (ft_strnstr(envp[i], "PATH", 4) == 0)
			i++;
	}
	if (!envp[i])
		return (0);
	return (i);
}

int	contains_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	is_only_pipe(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != '|')
		return (0);
	while (str[i])
	{
		if (str[i] != '|')
			return (0);
		i++;
	}
	return (i >= 1);
}

int	is_only_and(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != '&')
		return (0);
	while (str[i])
	{
		if (str[i] != '&')
			return (0);
		i++;
	}
	return (1);
}
