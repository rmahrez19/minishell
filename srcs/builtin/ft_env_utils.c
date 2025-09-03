/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:16:25 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/01 15:17:53 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	has_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	print_env_error(char *arg, int exit_code)
{
	if (exit_code == 126)
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': Permission denied", 2);
		return (126);
	}
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
}
