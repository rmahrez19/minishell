/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:58:53 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 16:32:06 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo_token_arg(char *arg, t_data *data, t_builtin *s)
{
	while (s->i < (int)ft_strlen(arg))
	{
		if (arg[s->i] == '\'')
			s->i += print_between_quote(arg, s->i, '\'', data);
		else if (arg[s->i] == '\"')
			s->i += print_between_quote(arg, s->i, '"', data);
		else if (arg[s->i] == '$' && (s->i == 0 || arg[s->i - 1] != '\\'))
		{
			s->expanded = expand_variables(arg + s->i, data);
			if (!s->expanded)
				return (0);
			if (!ft_strcmp(s->expanded, "*") && ft_strcmp(arg + s->i, "*"))
				return (free(s->expanded), 0);
			return (put_expanded(s), free(s->expanded), 0);
		}
		else if (arg && arg[s->i] != '\"' && arg[s->i] != '\''
			&& arg[s->i] != '\\')
			echo_token_arg_util(arg, s->i);
		else if (arg[s->i] == '\\')
			put_char_backslash(s, arg);
		else
			ft_putchar_fd(arg[s->i], 1);
		s->i++;
	}
	return (0);
}

int	launch_echo_token(char *arg, t_data *data)
{
	t_builtin	s;

	s.i = 0;
	if (!ft_strncmp(arg, "$\"\"", 4))
		return (0);
	return (echo_token_arg(arg, data, &s));
}

static int	echo_body(t_token *temp, t_data *data)
{
	t_token	*next;
	char	*tmp;

	while (temp)
	{
		if (temp->arg && temp->double_quote)
		{
			tmp = ft_strjoin("\"", temp->arg);
			if (!tmp)
				return (0);
			free(temp->arg);
			temp->arg = ft_strjoin(tmp, "\"");
			if (!temp->arg)
				return (free(tmp), 1);
			free(tmp);
		}
		if (temp->arg)
			launch_echo_token(temp->arg, data);
		if (!temp->colle_next)
			ft_putstr_fd(" ", 1);
		next = temp->next;
		temp = next;
	}
	return (0);
}

int	ft_echo(t_token *lst, t_data *data)
{
	t_token	*temp;
	int		newline;

	if (!lst || !lst->next)
		return (write(1, "\n", 1), 0);
	temp = lst->next;
	newline = 1;
	temp = lst->next;
	while (temp && is_valid_n_flag(temp->arg))
	{
		newline = 0;
		temp = temp->next;
	}
	echo_body(temp, data);
	if (newline)
		printf("\n");
	return (0);
}

int	ft_echo_pipe(char **args, t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		if (args[i])
			launch_echo_token(args[i], data);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
