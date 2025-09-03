/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:18:56 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:18:32 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	join_exit_utils(t_builtin *s)
{
	s->ft_m = 0;
	s->count = 0;
	s->res = ft_strdup("");
}

char	*join_exit_argument_if_possible(t_token *lst,
		t_token **next_after, int *token_count)
{
	t_builtin	s;

	join_exit_utils(&s);
	while (lst && (lst->type == CMD || lst->type == ARG))
	{
		s.tmp = remove_quotes_and_concatenate(lst->arg);
		if (!s.tmp)
			break ;
		s.joined = ft_strjoin(s.res, s.tmp);
		if (s.ft_m == 0)
			free(s.res);
		else
			ft_free();
		free(s.tmp);
		s.res = ft_malloc(ft_strlen(s.joined) + 1);
		s.ft_m = 1;
		if (!s.res)
			return (free(s.joined), NULL);
		ft_strlcpy(s.res, s.joined, ft_strlen(s.joined) + 1);
		free(s.joined);
		s.count++;
		lst = lst->next;
	}
	return (*next_after = lst, *token_count = s.count, s.res);
}

int	has_double_quote(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) <= 4)
		return (0);
	if (str[i] == '\'' || str[i] == '\"')
	{
		i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			i = ft_strlen(str) - 1;
			if (str[i] == '\'' || str[i] == '\"')
			{
				i--;
				if (str[i] == '\'' || str[i] == '\"')
					return (1);
			}
		}
	}
	return (0);
}

int	ft_exit_cmd(t_token *lst, t_data *data)
{
	t_exit	s;

	ft_exit_utils(&s, lst, data);
	if (s.nb)
	{
		while (s.tmp)
		{
			if ((!is_numeric(s.tmp->arg) && has_double_quote(s.tmp->arg))
				|| (!is_numeric(s.tmp->arg) && s.tmp->double_quote))
				return (print_error2(data, s.tmp, 1), ft_free(), 2);
			s.tmp = s.tmp->next;
		}
	}
	if (!is_long_long_range(lst->next->arg))
		return (print_error2(data, lst->next, 2), ft_free(), 2);
	if (!is_numeric(lst->next->arg) && !ft_atoi(lst->next->arg +1))
		return (print_error2(data, lst->next, 2), ft_free(), 2);
	if (s.tok_count > 1 && !(lst->next->arg[0] == '\''
			|| lst->next->arg[0] == '"' || s.next))
		return (print_error1(), data->exit_code = 1, ft_free(), 1);
	exit(ft_exit(data, s.arg));
}

int	ft_exit(t_data *data, char *arg)
{
	int	code;

	ft_putendl_fd("exit", 1);
	code = 0;
	if (arg && arg[0] == '\'')
	{
		code = ft_atoi(arg + 1);
		ft_free();
	}
	else if (arg)
	{
		code = ft_atoi(arg);
		ft_free();
	}
	else
		code = 0;
	data->exit_code = (unsigned char)code;
	if (data && data->env_tab)
		free_tab(data->env_tab);
	rl_clear_history();
	free_token_list_exit(data->lst);
	close_all_fds();
	return ((unsigned char)code);
}
