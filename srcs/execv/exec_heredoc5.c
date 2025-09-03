/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:36:58 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 19:42:12 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	collect_heredocs(t_token *lst, t_data *data)
{
	t_exec	s;

	s.start = lst;
	init_heredoc_fd(lst);
	while (lst)
	{
		if (lst->type == HEREDOC && lst->next)
		{
			s.limiter = remove_quotes(lst->next->arg, &s);
			s.fd = read_one_heredoc(s.limiter,
					contains_quote(lst->next->arg), data);
			if (s.fd == -1)
			{
				data->exit_code = 130;
				close_heredoc_fds(data->start);
				free(s.limiter);
				return (-1);
			}
			lst->heredoc_fd = s.fd;
			free(s.limiter);
		}
		lst = lst->next;
	}
	return (0);
}

char	*generate_heredoc_filename(void)
{
	static int	counter;
	t_exec		s;

	counter = 0;
	s.pid_str = ft_strdup("");
	if (!s.pid_str)
		return (NULL);
	s.count_str = ft_itoa(counter);
	if (!s.count_str)
		return (free(s.pid_str), NULL);
	s.temp = ft_strjoin(".heredoc.tmp_", s.pid_str);
	if (!s.temp)
		return (free(s.pid_str), free(s.count_str), NULL);
	s.filename = ft_strjoin(s.temp, "_");
	free(s.temp);
	if (!s.filename)
		return (free(s.pid_str), free(s.count_str), NULL);
	s.temp = ft_strjoin(s.filename, s.count_str);
	free(s.filename);
	free(s.pid_str);
	free(s.count_str);
	if (!s.temp)
		return (NULL);
	counter++;
	return (s.temp);
}

int	adding_value_heredoc(t_exec *s)
{
	s->line = NULL;
	s->filename = generate_heredoc_filename();
	s->fd = open(s->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (s->fd == -1)
		return (free(s->filename), perror("open heredoc write"), 1);
	if (s->fd != -1)
		close(s->fd);
	return (0);
}

void	init_heredoc_fd(t_token *lst)
{
	t_token	*init;

	init = lst;
	while (init)
	{
		init->heredoc_fd = -1;
		init = init->next;
	}
}

void	quit_signal(t_exec *s, t_data *data)
{
	if (s->fd != -1)
		close(s->fd);
	unlink(s->filename);
	free(s->filename);
	printf("heredoc > \n");
	g_code_signaux = 130;
	data->exit_code = 130;
	close_heredoc_fds(data->start);
}
