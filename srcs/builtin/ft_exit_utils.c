/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:27:14 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 21:02:56 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_error1(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
}

void	print_error2(t_data *data, t_token *lst, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		if (!lst->double_quote)
			put_error_without_single_quote(lst->arg);
		else
			ft_putstr_fd(lst->arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(ft_exit(data, "2"));
	}
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(lst->arg, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(ft_exit(data, "2"));
	}
}

void	put_error_without_single_quote(char *str)
{
	size_t	i;
	int		count;

	if (!str)
		return ;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	i = 0;
	if (count % 2)
		count--;
	while (str[i])
	{
		if (str[i] == '\'' && count > 0)
			i++;
		else if (str[i] == '$')
			i++;
		else
			write(2, &str[i++], 1);
	}
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_utils(t_exit *s, t_token *lst, t_data *data)
{
	if (!lst->next)
		exit(ft_exit(data, NULL));
	s->tmp = lst->next;
	s->arg = join_exit_argument_if_possible(lst->next, &s->next, &s->tok_count);
	if (!s->arg)
		return ;
	if (s->arg[0] == '\'')
		s->nb = ft_atoi(s->arg + 1);
	else
		s->nb = ft_atoi(s->arg);
}
