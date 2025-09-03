/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:24:40 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/16 16:52:35 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd_too_many_args(t_token *lst)
{
	if (lst && lst->next && lst->next->next)
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	return (0);
}

int	print_option_issues(char *path)
{
	ft_putstr_fd("minishell: cd : ", 2);
	if (ft_strlen(path) > 1)
		write(2, path, 2);
	else
		ft_putstr_fd(path, 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (2);
}

void	prefix(void)
{
	ft_putstr_fd("minishell: cd : ", 2);
}

int	is_empty_var(const char *var_name, char **env)
{
	int		i;
	size_t	len;
	char	*prefix;

	if (!var_name || !env)
		return (0);
	len = ft_strlen(var_name);
	prefix = ft_strjoin(var_name, "=");
	if (!prefix)
		return (0);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], prefix, len + 1))
		{
			free(prefix);
			return (env[i][len + 1] == '\0');
		}
		i++;
	}
	free(prefix);
	return (0);
}

int	manage_expanded(t_data *data, char *expanded, char *path)
{
	if (!ft_strcmp(path, "$HOME") && !env_var_exists("HOME", data->env_tab))
		return (ft_putendl_fd("bash: cd: HOME not set", 2), 1);
	else if (!ft_strcmp(path, "$HOME")
		&& env_var_exists("HOME", data->env_tab))
		return (0);
	if (chdir(expanded) == -1)
		return (prefix(), perror(expanded), free(expanded), 1);
	return (free(expanded), update_pwd(data));
}
