/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:55:07 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/02 17:40:43 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_var_exists(char *key, char **envp)
{
	int		i;
	size_t	len;

	if (!key || !envp)
		return (0);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (1);
		i++;
	}
	if (!ft_strcmp(key, "$?"))
		return (1);
	return (0);
}

int	is_good_token(t_token *lst)
{
	char	*temp;

	if (!ft_strcmp(lst->arg, ""))
		return (0);
	if (lst->double_quote)
	{
		temp = malloc(ft_strlen(lst->arg) + 3);
		if (!temp)
			return (2);
		temp[0] = '"';
		ft_strlcpy(temp + 1, lst->arg, ft_strlen(lst->arg));
		temp[ft_strlen(temp)] = '"';
		free(lst->arg);
		lst->arg = temp;
		return (0);
	}
	return (1);
}

void	put_error_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 126)
			write(2, &str[i], 1);
		i++;
	}
}

int	check_token_validity(t_token *lst)
{
	t_token	*temp;

	temp = lst->next;
	while (temp)
	{
		is_good_token(temp);
		temp = temp->next;
	}
	temp = lst->next;
	while (temp)
	{
		if (is_event_in_token(temp->arg))
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	find_tiniest_ascii(char **env, int *printed)
{
	int	i;
	int	min_index;

	i = 0;
	min_index = -1;
	while (env[i])
	{
		if (!printed[i])
		{
			if (min_index == -1 || ft_strcmp(env[i], env[min_index]) < 0)
				min_index = i;
		}
		i++;
	}
	return (min_index);
}
