/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 01:35:45 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 00:13:59 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_parent_proc(t_exec *s, t_data *data)
{
	waitpid(s->pid, &s->status, 0);
	if (s->fd != -1)
		close(s->fd);
	if ((WIFSIGNALED(s->status) && WTERMSIG(s->status) == SIGINT)
		|| (WIFEXITED(s->status) && WEXITSTATUS(s->status) == 130))
		return (quit_signal(s, data), -1);
	return (0);
}

void	write_in_file(t_exec *s)
{
	s->fd = open(s->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	ft_putendl_fd(s->line, s->fd);
	if (s->fd != -1)
		close(s->fd);
	free(s->line);
}

void	replace_ptrs(t_exec *s, t_data *data)
{
	s->expanded = expand_variables(s->line, data);
	free(s->line);
	s->line = s->expanded;
}

int	launch_reading(char *limiter, int quoted, t_data *data, t_exec *s)
{
	s->pid = fork();
	if (s->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			s->line = readline("heredoc > ");
			if (!s->line || !ft_strcmp(s->line, limiter))
				break ;
			if (!quoted)
				replace_ptrs(s, data);
			write_in_file(s);
		}
		ending(s);
	}
	else if (s->pid > 0)
	{
		if (exec_parent_proc(s, data) == -1)
			return (-1);
	}
	s->fd = open(s->filename, O_RDONLY);
	return (unlink(s->filename), free(s->filename), s->fd);
}

int	read_one_heredoc(char *limiter, int quoted, t_data *data)
{
	t_exec	s;

	if (adding_value_heredoc(&s))
		return (close_heredoc_fds(data->start), -1);
	return (launch_reading(limiter, quoted, data, &s));
}
