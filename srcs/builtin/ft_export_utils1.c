/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:53:21 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 23:39:43 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	if (s1)
		ft_memcpy(res, s1, len1);
	if (s2)
		ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	if (s1)
		free(s1);
	return (res);
}

char	*get_env_value(char *key, t_data *data)
{
	int		i;
	size_t	len;

	if (!key || !data || !data->env_tab)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (data->env_tab[i])
	{
		if (!ft_strncmp(data->env_tab[i], key, len)
			&& data->env_tab[i][len] == '=')
			return (data->env_tab[i] + len + 1);
		i++;
	}
	return ("");
}

int	is_valid_key(char *str)
{
	int		i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	get_env_index(char **env, char *arg)
{
	int		i;
	size_t	len;

	len = 0;
	i = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], arg, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	update_env(char ***env, char *arg)
{
	int		i;
	char	**new_env;
	int		count;

	i = get_env_index(*env, arg);
	if (i != -1)
	{
		free((*env)[i]);
		return ((*env)[i] = ft_strdup(arg), 1);
	}
	count = 0;
	while ((*env)[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (1);
	i = 0;
	while (i < count)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i++] = ft_strdup(arg);
	new_env[i] = NULL;
	return (free(*env), *env = new_env, 0);
}
