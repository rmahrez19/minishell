/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 15:51:17 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/03 13:10:19 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	variable_size(char *variable)
{
	int	i;

	i = 0;
	while (variable[i])
	{
		if (variable[i] == '=')
			break ;
		else
			i++;
	}
	return (i);
}

char	*find_line(char *variable, char **envp)
{
	int	i;

	i = 0;
	(void)variable;
	(void)envp;
	if (variable[0] != '$')
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(variable + 1, envp[i], variable_size(envp[i])))
			break ;
		i++;
	}
	if (envp[i])
		return (envp[i]);
	return (NULL);
}

char	*find_env(char *variable, char **envp)
{
	t_builtin	s;

	s.i = 0;
	s.j = 0;
	if (variable[0] != '$')
		return (NULL);
	while (envp[s.i])
	{
		if (!ft_strncmp(variable + 1, envp[s.i], ft_strlen(variable + 1)))
			break ;
		s.i++;
	}
	if (envp[s.i])
	{
		while (envp[s.i][s.j])
		{
			if (envp[s.i][s.j] == '=' && (size_t)s.j == ft_strlen(variable + 1))
			{
				s.j++;
				return (envp[s.i] + s.j);
			}
			s.j++;
		}
	}
	return (NULL);
}
