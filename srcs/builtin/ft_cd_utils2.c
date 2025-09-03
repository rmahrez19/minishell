/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:35:34 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/16 16:39:25 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	update_oldpwd(t_data *data, char *current_pwd)
{
	char	*old_pwd;
	int		j;

	old_pwd = ft_strjoin("OLDPWD=", current_pwd);
	if (!old_pwd)
		return ;
	j = 0;
	while (data->env_tab[j])
	{
		if (!ft_strncmp(data->env_tab[j], "OLDPWD=", 7))
		{
			free(data->env_tab[j]);
			data->env_tab[j] = old_pwd;
			return ;
		}
		j++;
	}
	free(old_pwd);
}

static int	update_env_pwd(t_data *data, char *new_pwd)
{
	int	i;

	i = 0;
	while (data->env_tab[i])
	{
		if (!ft_strncmp(data->env_tab[i], "PWD=", 4))
		{
			free(data->env_tab[i]);
			data->env_tab[i] = new_pwd;
			return (0);
		}
		i++;
	}
	free(new_pwd);
	return (0);
}

int	update_pwd(t_data *data)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;
	int		i;

	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_putstr_fd("cd : ", 2), perror("getcwd"), 1);
	new_pwd = ft_strjoin("PWD=", cwd);
	if (!new_pwd)
		return (1);
	i = 0;
	while (data->env_tab[i])
	{
		if (!ft_strncmp(data->env_tab[i], "PWD=", 4))
		{
			update_oldpwd(data, data->env_tab[i] + 4);
			break ;
		}
		i++;
	}
	return (update_env_pwd(data, new_pwd));
}

int	cd_home_case(t_data *data)
{
	if (!env_var_exists("HOME", data->env_tab))
		return (ft_putendl_fd("bash: cd: HOME not set", 2), 1);
	if (is_empty_var("HOME", data->env_tab))
		return (0);
	return (cd_go_home(data));
}

int	cd_dash_case(t_data *data)
{
	char	*oldpwd;

	oldpwd = find_env("$OLDPWD", data->env_tab);
	if (!oldpwd)
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		data->exit_code = 1;
		return (1);
	}
	ft_putendl_fd(oldpwd, 1);
	if (chdir(oldpwd) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(oldpwd);
		data->exit_code = 1;
		return (1);
	}
	return (update_pwd(data));
}
