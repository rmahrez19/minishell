/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parsing_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:36:14 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 17:24:19 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_unexpected(char *token)
{
	int	i;

	if (token)
		i = ft_strlen(token);
	ft_putstr_fd("minishell: syntax error", 2);
	ft_putstr_fd(" near unexpected token `", 2);
	if (token)
	{
		while (i >= 0)
		{
			if (token)
			{
				if (token[i] != '|' && token[i] != '<' && token[i] != '>')
					i--;
			}
			else
				break ;
			ft_putchar_fd(token[i], 2);
			ft_putendl_fd("'", 2);
			break ;
		}
	}
}

int	has_unexpected_token(t_exec *s)
{
	t_token	*curr;
	t_token	*next;

	curr = s->check;
	while (curr)
	{
		next = curr->next;
		if (is_operator_str(curr->arg))
		{
			if (!next || is_operator_str(next->arg))
			{
				print_unexpected(NULL);
				if (!ft_strcmp(curr->arg, "|"))
					ft_putstr_fd("|", 2);
				else if (!next)
					ft_putstr_fd("newline", 2);
				else
					ft_putstr_fd(next->arg, 2);
				ft_putendl_fd("'", 2);
				return (1);
			}
		}
		curr = curr->next;
	}
	return (0);
}

void	analyze_tokens(t_exec *s)
{
	while (s->tmp)
	{
		if (s->tmp->type == HEREDOC)
			s->has_heredoc = 1;
		else if (s->tmp->type == PIPE)
			s->has_pipe = 1;
		else if (s->tmp->type == INPUT || s->tmp->type == TRUNC
			|| s->tmp->type == APPEND)
		{
			s->has_redir = 1;
			if (s->tmp->type == TRUNC
				|| (s->tmp->type == APPEND && s->tmp->next))
				s->tmp->next->type = 13;
		}
		else if (s->tmp->type == CMD || s->tmp->type == ARG)
			s->has_cmd = 1;
		if (is_builtin(s->tmp->arg))
			s->from_builtin = 1;
		s->tmp = s->tmp->next;
	}
	if (s->has_pipe && s->from_builtin)
		s->from_builtin = 0;
}

int	is_only_chevron(char *str)
{
	int	i;

	if (!str || (str[0] != '<' && str[0] != '>'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != '<' && str[i] != '>')
			return (0);
		i++;
	}
	return (1);
}

int	no_args_in_lst(t_token *lst, t_data *data)
{
	t_token	*temp;

	temp = lst;
	while (temp)
	{
		if (!is_only_chevron(temp->arg))
			return (0);
		temp = temp->next;
	}
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (ft_strlen(lst->arg) > 1)
		write(2, lst->arg, 2);
	else
		write(2, lst->arg, 1);
	ft_putstr_fd("'\n", 2);
	data->exit_code = 2;
	return (1);
}
