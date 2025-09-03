/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:18:54 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/04 14:35:39 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_tab_size(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	add_env_entry(char ***env_tab, char *new_entry)
{
	int		size;
	char	**new_tab;
	int		i;

	size = 0;
	while ((*env_tab)[size])
		size++;
	new_tab = malloc(sizeof(char *) * (size + 2));
	if (!new_tab)
		return (1);
	i = 0;
	while (i < size)
	{
		new_tab[i] = (*env_tab)[i];
		i++;
	}
	new_tab[i++] = ft_strdup(new_entry);
	new_tab[i] = NULL;
	free(*env_tab);
	*env_tab = new_tab;
	return (0);
}

char	**duplicate_envp(char **envp, char *var)
{
	t_utils	s;

	s.env_tab = malloc(sizeof(char *) * (get_tab_size(envp) + 1));
	if (!s.env_tab)
		return (NULL);
	s.i = 0;
	s.j = 0;
	while (envp[s.i])
	{
		if (!var || ft_strncmp(var, envp[s.i], ft_strlen(var)) != 0)
		{
			s.env_tab[s.j] = ft_strdup(envp[s.i]);
			if (!s.env_tab[s.j])
			{
				free_tab(s.env_tab);
				return (NULL);
			}
			s.j++;
		}
		s.i++;
	}
	s.env_tab[s.j] = NULL;
	add_missing_entry(&s.env_tab);
	return (s.env_tab);
}
