/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:25:48 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 18:06:22 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_cmd_not_found(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	if (errno == EACCES && !ft_strncmp(str, "/", 1))
	{
		ft_putendl_fd(" : Is a directory", 2);
		return (126);
	}
	else if (errno == EACCES || !ft_strncmp(str, "./", 2))
	{
		ft_putendl_fd(" : permission denied", 2);
		return (126);
	}
	else
	{
		ft_putendl_fd(" : command not found", 2);
		close_all_fds();
		return (127);
	}
	return (0);
}

int	pid_result(int *pid_tab, int pid_count)
{
	int	i;
	int	status;
	int	exit_code;
	int	sig;

	status = 0;
	i = 0;
	while (i < pid_count)
		waitpid(pid_tab[i++], &status, 0);
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		exit_code = 128 + sig;
	}
	else if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = 1;
	return (exit_code);
}

void	restore_std_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}
