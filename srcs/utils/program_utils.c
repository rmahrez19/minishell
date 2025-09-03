/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:33:28 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 00:20:42 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**free_tab(char **tab)
{
	int	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
	return (NULL);
}

int	lstsize(t_token *lst)
{
	int		i;
	t_token	*nodes;

	i = 0;
	nodes = lst;
	while (nodes != NULL)
	{
		i++;
		nodes = nodes -> next;
	}
	return (i);
}

void	bzero_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		str[i++] = 0;
}

int	is_long_long_range(char *str)
{
	t_utils	s;

	if (str[0] == '\'')
		s.ptr = str + 1;
	else
		s.ptr = str;
	s.sign = 1;
	s.result = 0;
	s.i = 0;
	if (s.ptr[s.i] == '+' || s.ptr[s.i] == '-')
	{
		if (s.ptr[s.i++] == '-')
			s.sign = -1;
	}
	while (s.ptr[s.i])
	{
		if (!ft_isdigit(s.ptr[s.i]) && s.i != (int)ft_strlen(s.ptr + 1))
			return (0);
		s.result = s.result * 10 + (s.ptr[s.i] - '0');
		if ((s.sign == 1 && s.result > LLONG_MAX)
			|| (s.sign == -1 && s.result > (unsigned long long)LLONG_MAX + 1))
			return (0);
		s.i++;
	}
	return (1);
}

void	free_token_list_exit(t_token *lst)
{
	t_token	*temp;

	while (lst)
	{
		temp = lst->next;
		if (lst->arg)
			free(lst->arg);
		free(lst);
		lst = temp;
	}
	close_all_fds();
}
