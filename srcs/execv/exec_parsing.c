/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:22:17 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:36:03 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_dispatch(t_token *lst, t_data *data, t_exec *s)
{
	if (create_redirection_file(lst, data) == 1)
		return (free_token_list_exit(lst), cafd(), data->exit_code = 1, 1);
	reorganize_linked_list(lst);
	if (s->from_builtin && !s->has_heredoc && !s->has_redir)
		return (exec_builtin(lst, data));
	else if (s->has_redir && lstsize(lst) == 1)
		return (print_unexpected("newline"), data->exit_code = 2, 0);
	else if (s->has_pipe && (!lst || lst->type == PIPE))
		return (data->exit_code = 2, print_unexpected("|"), 0);
	else if (s->has_heredoc && lstsize(lst) > 1)
		return (launch_heredoc_pipes(lst, data), 0);
	else if (s->has_heredoc && lstsize(lst) == 1)
		return (print_unexpected("newline"),
			data->exit_code = 2, 0);
	else if (s->has_cmd)
		return (launch_commands(lst, data), 0);
	return (free_token_list_exit(lst), close_all_fds(), 1);
}

void	expand_tilde(t_data *data)
{
	char	*env;

	ft_putstr_fd("minishell: ", 2);
	env = find_env("$HOME", data->env_tab);
	if (env)
	{
		ft_putstr_fd(env, 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
}

int	wrong_nb_heredoc(t_token *lst)
{
	int		i;
	t_token	*temp;

	temp = lst;
	while (temp)
	{
		i = 0;
		if (temp->arg[i] == '<')
		{
			while (temp->arg[i] == '<')
				i++;
			if (i >= 5)
				return (print_unexpected("<<"), 1);
		}
		temp = temp->next;
	}
	return (0);
}

int	exec(t_token *lst, t_data *data)
{
	t_exec	s;

	if (!ft_strcmp(lst->arg, "~"))
		return (expand_tilde(data), data->exit_code = 126, 1);
	if (!ft_strcmp(lst->arg, "."))
		return (ft_putstr_fd("minishell: .: filename argument required\n", 2),
			free_token_list_exit(lst), close_all_fds(), data->exit_code = 2, 2);
	set_values(&s, lst);
	if ((!ft_strcmp(lst->arg, """") && lstsize(lst) == 1)
		|| (!ft_strcmp(lst->arg, "''") && lstsize(lst) == 1))
		return (ft_putstr_fd("minishell: : command not found\n", 2),
			data->exit_code = 127, free_token_list_exit(lst), cafd(), 1);
	if (is_a_directory(lst, data))
		return (free_token_list_exit(lst), close_all_fds(), 1);
	if (is_bad_tokens(lst))
		return (free_token_list_exit(lst), cafd(), data->exit_code = 2, 1);
	if (s.check && has_unexpected_token(&s))
		return (free_token_list_exit(lst), cafd(), data->exit_code = 2, 1);
	if (no_args_in_lst(lst, data))
		return (free_token_list_exit(lst), close_all_fds(), 1);
	if (wrong_nb_heredoc(lst))
		return (data->exit_code = 2, 1);
	analyze_tokens(&s);
	return (exec_dispatch(lst, data, &s));
}
