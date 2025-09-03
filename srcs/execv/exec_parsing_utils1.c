/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:36:17 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/31 18:46:50 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_a_directory(t_token *lst, t_data *data)
{
	if (is_only_backslashes(lst->arg))
	{
		data->exit_code = print_cmd_not_found(lst->arg);
		return (1);
	}
	if (!ft_strcmp(lst->arg, ".."))
		return (data->exit_code = print_cmd_not_found(".."), 1);
	if (is_only_slashes(lst->arg) || is_recursive_path(lst->arg))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (data->exit_code = 126, 1);
	}
	if (!ft_strcmp(lst->arg, "/."))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (data->exit_code = 126, 1);
	}
	if (!ft_strcmp(lst->arg, "<>"))
		ft_putstr_fd("minishell: parse error near `newline'", 2);
	return (0);
}

void	set_values(t_exec *s, t_token *lst)
{
	s->tmp = lst;
	s->check = lst;
	s->has_heredoc = 0;
	s->has_pipe = 0;
	s->has_redir = 0;
	s->has_cmd = 0;
	s->from_builtin = 0;
	s->and_if = 0;
}

int	is_operator_str(char *s)
{
	return (!ft_strcmp(s, "|") || !ft_strcmp(s, "||") || !ft_strcmp(s, "&&")
		|| !ft_strcmp(s, "<") || !ft_strcmp(s, "<<")
		|| !ft_strcmp(s, ">") || !ft_strcmp(s, ">>"));
}
