/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:01:17 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:22:08 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_only_point_virgule(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != ';')
		return (0);
	while (str[i])
	{
		if (str[i] != ';')
			return (0);
		i++;
	}
	return (1);
}

int	is_only_slashes(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != '/')
		return (0);
	while (str[i])
	{
		if (str[i] != '/')
			return (0);
		i++;
	}
	return (i >= 1);
}

int	is_only_backslashes(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != '\'')
		return (0);
	while (str[i])
	{
		if (str[i] != '\'')
			return (0);
		i++;
	}
	return (i >= 1);
}

int	is_recursive_path(char *str)
{
	char	**parts;
	int		i;

	if (!str)
		return (0);
	if (str[0] != '/' && str[0] != '.')
		return (0);
	parts = ft_split(str, '/');
	if (!parts)
		return (0);
	i = 0;
	while (parts[i])
	{
		if (ft_strcmp(parts[i], ".") != 0 && ft_strcmp(parts[i], "..")
			!= 0 && parts[i][0] != '\0')
		{
			free_tab(parts);
			return (0);
		}
		i++;
	}
	free_tab(parts);
	return (1);
}

int	manage_bad_fd(t_data *data)
{
	t_token	*temp;
	int		fd;

	temp = data->lst;
	close_heredoc_fds(data->start);
	while (temp)
	{
		if (temp->type == TRUNC || temp->type == APPEND)
		{
			if (temp ->next-> arg)
				fd = open(temp->next->arg, O_RDONLY);
			else
				return (0);
			if (fd == -1)
				return (print_cmd_not_found(temp->next->arg),
					close_heredoc_fds(data->start), data->exit_code = 1,
					free_token_list_exit(data->start), close_all_fds(), 0);
			else
				close(fd);
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return (data->exit_code = 1, 0);
}
