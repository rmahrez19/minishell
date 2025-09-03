/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:40:24 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:33:40 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	child_process_heredoc(t_exec *s, t_token **start,
			t_exec *st, t_data *data)
{
	s->tmp = *start;
	while (s->tmp && s->tmp != s->end)
	{
		if (s->tmp->type == HEREDOC && s->tmp->heredoc_fd != -1)
		{
			dup2_and_close_in(s->tmp->heredoc_fd);
			break ;
		}
		s->tmp = s->tmp->next;
	}
	s->tmp = *start;
	while (s->tmp && s->tmp != s->end)
		manage_input(s);
	if (st->fd_out != -1)
		dup2_and_close_out(st->fd_out);
	if (!st->is_last)
	{
		close(s->pipefd[0]);
		dup2_and_close_out(s->pipefd[1]);
	}
	close_heredoc_fds(data->start);
	exec_cmd_array(s->args, data, st);
	return (1);
}

void	parent_process_heredoc(int is_last, t_exec *s, t_data *data)
{
	if (!is_last)
	{
		close(s->pipefd[1]);
		dup2_and_close_in(s->pipefd[0]);
	}
	close_heredoc_fds(data->start);
}

pid_t	handle_command(t_token **lst, t_token **start,
	t_exec *st, t_data *data)
{
	t_exec	s;

	s.end = *lst;
	while (s.end && s.end->type != PIPE)
		s.end = s.end->next;
	s.args = build_args_from_tokens_heredoc(*start, s.end, data);
	if (!s.args)
		return (close_heredoc_fds(data->start), -1);
	if (!s.args[0])
		return (free_tab(s.args), close_heredoc_fds(data->start), -1);
	if (!st->is_last && pipe(s.pipefd) == -1)
		return (close_heredoc_fds(data->start), free_tab(s.args), -1);
	s.pid = fork();
	if (s.pid == -1)
		return (close_heredoc_fds(data->start), free_tab(s.args), -1);
	if (s.pid == 0)
		child_process_heredoc(&s, start, st, data);
	else
		parent_process_heredoc(st->is_last, &s, data);
	free_tab(s.args);
	*lst = s.end;
	if (*lst && (*lst)->type == PIPE)
		*lst = (*lst)->next;
	*start = *lst;
	return (s.pid);
}

void	heredoc_pipes_process(t_exec *s, t_token *lst, t_data *data)
{
	s->pid_count = 0;
	s->start = lst;
	while (lst)
	{
		s->is_last = (lst->next == NULL);
		if (lst->type == PIPE || s->is_last)
		{
			s->fd_out = get_outfile_fd(s->start, lst);
			s->prev = lst;
			s->pids[s->pid_count++] = handle_command(&lst, &s->start, s, data);
			if (lst == s->prev)
				lst = lst->next;
			if (s->fd_out != -1)
				close(s->fd_out);
		}
		else
			lst = lst->next;
	}
	if (s->pid_count)
		data->exit_code = pid_result(s->pids, s->pid_count);
	close_heredoc_fds(data->start);
	restore_std_fds(s->backups[0], s->backups[1]);
}

int	launch_heredoc_pipes(t_token *lst, t_data *data)
{
	t_exec	s;

	s.start = lst;
	if (checking_heredoc(lst))
		return (1);
	if (collect_heredocs(lst, data) == -1)
	{
		data->exit_code = 130;
		close_heredoc_fds(data->start);
		free_token_list_exit(data->start);
		return (close_all_fds(), 1);
	}
	if (data->bad_fd == -1)
		return (manage_bad_fd(data), 1);
	if (lst->type == HEREDOC)
		return (close_heredoc_fds(data->start),
			free_token_list_exit(lst), close_all_fds(), 0);
	s.backups[0] = dup(STDIN_FILENO);
	s.backups[1] = dup(STDOUT_FILENO);
	heredoc_pipes_process(&s, lst, data);
	close_heredoc_fds(data->start);
	free_token_list_exit(lst);
	close_all_fds();
	return (0);
}
