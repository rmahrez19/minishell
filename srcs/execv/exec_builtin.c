/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:24:02 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:15:49 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd)
		|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd)
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd)
		|| !ft_strcmp("exit", cmd))
		return (1);
	return (0);
}

int	exec_builtin2(t_token *lst, t_data *data)
{
	if (!ft_strcmp("cd", lst->arg))
	{
		if (!ft_strcmp("cd", lst->arg))
		{
			data->exit_code = ft_cd(lst, data);
			return (free_token_list_exit(lst), close_all_fds(), 1);
		}
		else
		{
			free_token_list_exit(lst);
			return (close_all_fds(), data->exit_code = 127,
				ft_putstr_fd("cd: No such file or directory\n", 2), 1);
		}
	}
	if (!ft_strcmp("export", lst->arg))
	{
		data->exit_code = ft_export(lst, data);
		return (free_token_list_exit(lst), close_all_fds(), 1);
	}
	if (!ft_strcmp("exit", lst->arg))
	{
		data->exit_code = ft_exit_cmd(lst, data);
		return (free_token_list_exit(lst), close_all_fds(), 1);
	}
	return (0);
}

int	exec_builtin(t_token *lst, t_data *data)
{
	if (!ft_strcmp("echo", lst->arg))
	{
		data->exit_code = ft_echo(lst, data);
		return (free_token_list_exit(lst), close_all_fds(), 1);
	}
	else if (!ft_strcmp("pwd", lst->arg))
		return (data->exit_code = ft_pwd(lst), free_token_list_exit(lst), 1);
	else if (!ft_strcmp("env", lst->arg))
	{
		data->exit_code = ft_env(lst, data);
		return (free_token_list_exit(lst), close_all_fds(), 1);
	}
	else if (!ft_strcmp("unset", lst->arg))
	{
		if (lst->next)
			return (data->exit_code = ft_unset(lst, data),
				free_token_list_exit(lst), close_all_fds(), 1);
		else
			return (free_token_list_exit(lst), close_all_fds(),
				ft_putstr_fd("minishell: unset: not enough arguments\n", 2),
				data->exit_code = 1, 1);
	}
	return (exec_builtin2(lst, data));
}

int	exec_builtin_array(char **args, t_data *data, int *backups)
{
	if (!args || !args[0])
		return (1);
	if (!ft_strcmp(args[0], "echo"))
		data->exit_code = ft_echo_pipe(args, data);
	else if (!ft_strcmp(args[0], "pwd"))
		data->exit_code = ft_pwd_pipe(data);
	else if (!ft_strcmp(args[0], "env"))
		data->exit_code = ft_env_pipe(data);
	else if (!ft_strcmp(args[0], "unset"))
		data->exit_code = ft_unset_pipe(args, data);
	else if (!ft_strcmp(args[0], "cd"))
		data->exit_code = ft_cd_pipe(args, data);
	else if (!ft_strcmp(args[0], "exit"))
		data->exit_code = ft_exit(data, args[1]);
	else if (!ft_strcmp(args[0], "export"))
		data->exit_code = ft_export_pipe(args, data);
	else
		return (free_tab(args), 0);
	dup2(backups[0], STDIN_FILENO);
	dup2(backups[1], STDOUT_FILENO);
	close(backups[0]);
	close(backups[1]);
	free_tab(args);
	return (1);
}
