/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:49:12 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/04 14:37:51 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	remove_equal(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		while (env[i][j])
			j++;
		j--;
		if (env[i][j] == '=')
			env[i][j] = '\0';
		i++;
		j = 0;
	}
}

void	print_export_sorted(char **env)
{
	t_builtin	s;

	s.size = 0;
	while (env[s.size])
		s.size++;
	s.printed = malloc(sizeof(int) * s.size);
	if (!s.printed)
		return ;
	s.i = 0;
	while (s.i < s.size)
		s.printed[s.i++] = 0;
	remove_equal(env);
	s.i = 0;
	while (s.i < s.size)
	{
		s.min = find_tiniest_ascii(env, s.printed);
		if (s.min != -1)
		{
			ft_putstr_fd("export ", 1);
			ft_putendl_fd(env[s.min], 1);
			s.printed[s.min] = 1;
		}
		s.i++;
	}
	free(s.printed);
}

int	is_valid_option(char *str)
{
	if (str[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		write(2, &str[0], 1);
		write(2, &str[1], 1);
		ft_putstr_fd(": invalid option\n", 2);
		return (1);
	}
	return (0);
}

void	free_export_variables(t_builtin *s)
{
	free(s->key);
	free(s->val);
	free(s->tmp);
	free(s->joined);
}

int	count_args(t_token *lst)
{
	int		i;
	t_token	*temp;

	if (!lst->arg)
		return (0);
	i = 1;
	temp = lst;
	while (temp->next)
	{
		if (!temp->colle_next)
			i++;
		temp = temp->next;
	}
	return (i);
}
