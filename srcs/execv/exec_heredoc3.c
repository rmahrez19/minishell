/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:54:39 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:20:41 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_args_values(t_exec *s, t_token *start)
{
	s->count = 0;
	s->tmp = start;
	s->i = 0;
}

char	**build_args_from_tokens_heredoc(t_token *start,
			t_token *end, t_data *data)
{
	t_exec	s;

	set_args_values(&s, start);
	while (s.tmp && s.tmp != end)
	{
		if (s.tmp->type == HEREDOC && s.tmp->next)
			s.tmp = s.tmp->next;
		else if (s.tmp->type == CMD || s.tmp->type == ARG)
			s.count++;
		s.tmp = s.tmp->next;
	}
	s.args = malloc(sizeof(char *) * (s.count + 1));
	if (!s.args)
		return (NULL);
	set_args_values(&s, start);
	while (s.tmp && s.tmp != end)
	{
		if (s.tmp->type == HEREDOC && s.tmp->next)
			s.tmp = s.tmp->next;
		else if (s.tmp->type == CMD || s.tmp->type == ARG)
			s.args[s.i++] = expand_variables(s.tmp->arg, data);
		s.tmp = s.tmp->next;
	}
	s.args[s.i] = NULL;
	return (s.args);
}

int	get_outfile_fd(t_token *start, t_token *end)
{
	t_token	*tmp;
	int		fd;
	int		flags;

	tmp = start;
	fd = -1;
	while (tmp && tmp != end)
	{
		if ((tmp->type == TRUNC || tmp->type == APPEND) && tmp->next)
		{
			flags = O_WRONLY | O_CREAT;
			if (tmp->type == TRUNC)
				flags |= O_TRUNC;
			else
				flags |= O_APPEND;
			if (fd != -1)
				close(fd);
			fd = open(tmp->next->arg, flags, 0644);
		}
		tmp = tmp->next;
	}
	return (fd);
}

int	exec_cmd_array(char **args, t_data *data, t_exec *s)
{
	char	*path;

	if (!args || !args[0])
		exit(1);
	free_token_list_exit(data->lst);
	if (is_builtin(args[0]))
	{
		exec_builtin_array(args, data, s->backups);
		free_tab(args);
		exit(data->exit_code);
	}
	close(s->backups[0]);
	close(s->backups[1]);
	path = get_path(args[0], data->env_tab);
	if (!path)
	{
		data->exit_code = print_cmd_not_found(args[0]);
		free_tab(args);
		exit(data->exit_code);
	}
	execve(path, args, data->env_tab);
	perror("execve failed");
	return (free(path), free_tab(args), data->exit_code = 1, exit(1), 1);
}

void	ending(t_exec *s)
{
	free(s->line);
	exit(0);
}
