/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_entry_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 13:01:17 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/11 18:15:44 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_self_uid_str(void)
{
	struct stat	sb;
	char		*uid_str;

	if (stat("/proc/self", &sb) == -1)
		return (NULL);
	uid_str = ft_itoa(sb.st_uid);
	return (uid_str);
}

static int	add_pwd_if_missing(char ***env_tab)
{
	t_utils	s;

	if (!env_var_exists("PWD", *env_tab))
	{
		getcwd(s.path, sizeof(s.path));
		s.entry = malloc(ft_strlen(s.path) + 5);
		if (!s.entry)
			return (1);
		ft_strlcpy(s.entry, "PWD=", ft_strlen("PWD=") + 1);
		ft_strlcat(s.entry, s.path, ft_strlen("PWD=") + ft_strlen(s.path) + 1);
		add_env_entry(env_tab, s.entry);
		free(s.entry);
		ft_bzero(s.path, ft_strlen(s.path) + 1);
		ft_strlcpy(s.path, "OLDPWD", 7);
		add_env_entry(env_tab, s.path);
	}
	return (0);
}

static int	add_uid_if_missing(char ***env_tab)
{
	t_utils	s;

	s.uid_env = get_self_uid_str();
	if (!s.uid_env)
		return (1);
	s.entry = malloc(ft_strlen(s.uid_env) + 5);
	if (!s.entry)
		return (free(s.uid_env), 1);
	ft_strlcpy(s.entry, "UID=", ft_strlen("UID=") + 1);
	ft_strlcat(s.entry, s.uid_env, ft_strlen("UID=")
		+ ft_strlen(s.uid_env) + 1);
	add_env_entry(env_tab, s.entry);
	free(s.uid_env);
	free(s.entry);
	return (0);
}

int	update_shlvl(char ***env_tab, t_data *data)
{
	t_utils	s;
	int		nb;

	if (!env_var_exists("PWD", *env_tab))
	{
		s.entry = malloc(ft_strlen(s.path) + 5);
		if (!s.entry)
			return (1);
		ft_strlcpy(s.entry, "SHLVL=1", ft_strlen("SHLVL=1") + 1);
		add_env_entry(env_tab, s.entry);
		return (free(s.entry), 0);
	}
	s.entry = get_env_value("SHLVL", data);
	nb = ft_atoi(s.entry) + 1;
	remove_env_var(ft_strdup("SHLVL"), 0, data);
	s.ptr = ft_itoa(nb);
	if (!s.ptr)
		return (1);
	s.res = ft_strjoin("SHLVL=", s.ptr);
	if (!s.res)
		return (free(s.ptr), 1);
	add_env_entry(env_tab, s.res);
	return (free(s.res), free(s.ptr), 0);
}

void	add_missing_entry(char ***env_tab)
{
	add_uid_if_missing(env_tab);
	add_pwd_if_missing(env_tab);
}
