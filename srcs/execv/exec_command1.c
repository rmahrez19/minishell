/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 20:31:38 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:33:58 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_child_process(t_exec *st, t_data *data,
		int has_prev_pipe, int in_pipe)
{
	t_exec	s;

	if (has_prev_pipe)
		dup2_and_close_in(in_pipe);
	if (st->has_next)
		close_fds(st->pipefd[0], st->pipefd[1], -1, st->pipefd[1]);
	else if (handle_redirections_cmd(st->start, data) == -1)
		return (data->exit_code = 1, 1);
	if (!st->args || !st->args[0] || ft_strlen(st->args[0]) == 0)
		exit(0);
	if (is_builtin(st->args[0]))
		return (exec_builtin_array(st->args, data, data->backups),
			exit(data->exit_code), 0);
	s.path = get_path(st->args[0], data->env_tab);
	close_all_fds();
	if (s.path)
		execve(s.path, st->args, data->env_tab);
	free(s.path);
	s.err_fd = open("/dev/tty", O_WRONLY);
	if (s.err_fd != -1)
		data->exit_code = print_cmd_not_found(st->args[0]);
	return (close_fds(s.err_fd, data->backups[0], data->backups[1], -1),
		free_tab(st->args), exit(data->exit_code), 0);
}

int	set_command_segment_values(t_exec *s, t_data *data,
		t_token **lst, int *backups)
{
	s->start = *lst;
	s->args = build_args_and_advance(lst, data);
	s->has_next = (*lst != NULL);
	if (!s->args || !s->args[0] || (!s->args[0][0] && !s->start->double_quote))
	{
		close(backups[0]);
		close(backups[1]);
		close_all_fds();
		return (free_tab(s->args), 1);
	}
	if (!s->args[0][0] && s->start->double_quote)
	{
		close_all_fds();
		ft_putendl_fd("minishell: : command not found", 2);
		close(backups[0]);
		close(backups[1]);
		data->exit_code = 127;
		return (free_tab(s->args), 1);
	}
	return (0);
}

int	execute_parent_process(t_exec *s, int has_prev_pipe, int *in_pipe)
{
	if (has_prev_pipe)
		close(*in_pipe);
	if (s->has_next)
	{
		*in_pipe = s->pipefd[0];
		close(s->pipefd[1]);
	}
	else
	{
		if (*in_pipe > 2)
			close(*in_pipe);
		*in_pipe = -1;
	}
	return (0);
}

pid_t	execute_command_segment(t_token **lst, t_data *data,
			int has_prev_pipe, int *in_pipe)
{
	t_exec	s;

	if (set_command_segment_values(&s, data, lst, data->backups))
		return (-1);
	if (!s.has_next && !has_prev_pipe && is_builtin(s.args[0]))
	{
		if (handle_redirections_cmd(s.start, data) == -1)
			return (free_tab(s.args), data->exit_code = 1, -1);
		return (exec_builtin_array(s.args, data, data->backups), -1);
	}
	if (s.has_next && pipe(s.pipefd) == -1)
		return (perror("pipe failed"), close_all_fds(), free_tab(s.args), -1);
	s.pid = fork();
	if (s.pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_child_process(&s, data, has_prev_pipe, *in_pipe);
	}
	else
		execute_parent_process(&s, has_prev_pipe, in_pipe);
	return (free_tab(s.args), s.pid);
}

int	launch_commands(t_token *lst, t_data *data)
{
	t_exec	s;
	int		in_pipe;

	in_pipe = 0;
	init_struct(&s, lst);
	if (data->bad_fd == -1)
		return (manage_bad_fd(data), close_all_fds(), 0);
	data->backups[0] = dup(STDIN_FILENO);
	data->backups[1] = dup(STDOUT_FILENO);
	while (lst)
	{
		s.pid = execute_command_segment(&lst,
				data, s.has_prev_pipe, &in_pipe);
		if (s.pid > 0)
			s.pids[s.pid_count++] = s.pid;
		else
			return (free_token_list_exit(s.start), close_all_fds(), 0);
		s.has_next = (lst != NULL);
		s.has_prev_pipe = 1;
	}
	if (s.pid_count)
		data->exit_code = pid_result(s.pids, s.pid_count);
	return (free_token_list_exit(s.start),
		restore_std_fds(data->backups[0], data->backups[1]),
		close_all_fds(), 0);
}
