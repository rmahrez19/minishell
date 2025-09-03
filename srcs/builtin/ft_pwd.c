/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:36:09 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/31 17:11:15 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_invalid_pwd(char *str)
{
	if (str[0])
	{
		if (str[0] == '-')
		{
			ft_putstr_fd("minishell: pwd: ", 2);
			if (str[1])
				write(2, str, 2);
			else
				write(2, str, 1);
			ft_putstr_fd(": invalid option\n", 2);
			return (1);
		}
	}
	return (0);
}

int	ft_pwd(t_token *lst)
{
	char	buffer[PATH_MAX];

	if (lst->next)
	{
		if (is_invalid_pwd(lst->next->arg))
			return (2);
	}
	if (!ft_strncmp(lst->arg, "pwd", 4))
	{
		if (getcwd(buffer, PATH_MAX))
		{
			ft_putendl_fd(buffer, 1);
			return (0);
		}
		else
		{
			ft_putstr_fd("pwd: error retrieving current", 2);
			ft_putstr_fd(" directory: getcwd: cannot", 2);
			ft_putstr_fd(" access parent directories: ", 2);
			perror("");
			return (1);
		}
	}
	return (1);
}

int	ft_pwd_pipe(t_data *data)
{
	char	buffer[PATH_MAX];

	(void)data;
	if (getcwd(buffer, PATH_MAX))
	{
		ft_putendl_fd(buffer, 1);
		return (data->exit_code = 0, 0);
	}
	ft_putstr_fd("pwd: error retrieving current", 2);
	ft_putstr_fd(" directory: getcwd: cannot", 2);
	ft_putstr_fd(" access parent directories: ", 2);
	perror("");
	return (1);
}
