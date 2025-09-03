/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   building_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:17:19 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 22:05:03 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**managing_input_case(t_token **lst, t_data *data, t_exec *s)
{
	s->expanded = expand_variables((*lst)->next->arg, data);
	s->fd = open(s->expanded, O_RDONLY);
	if (s->fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s->expanded, 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		free(s->expanded);
		return (NULL);
	}
	close(s->fd);
	free_tab(s->args);
	s->args = malloc(sizeof(char *) * 3);
	s->args[0] = ft_strdup("cat");
	s->args[1] = ft_strdup(s->expanded);
	s->args[2] = NULL;
	free(s->expanded);
	s->i = 2;
	(*lst) = (*lst)->next->next->next;
	return (s->args);
}

void	adding_value(t_token **lst, t_exec *s, t_data *data)
{
	if ((*lst)->type == CMD)
		s->has_cmd = 1;
	if (check_simple_quote((*lst)->arg))
	{
		s->expanded = ft_strdup((*lst)->arg + 1);
		s->expanded[ft_strlen(s->expanded) - 1] = '\0';
	}
	else
		s->expanded = expand_variables((*lst)->arg, data);
	if (!s->args[s->i])
		s->args[s->i] = ft_strdup("");
	s->args[s->i] = ft_strjoin_free(s->args[s->i], s->expanded);
	free(s->expanded);
	if (!(*lst)->colle_next)
	{
		if (!ft_strcmp(s->args[s->i], "$?"))
		{
			free(s->args[s->i]);
			s->args[s->i] = ft_itoa(data->exit_code);
		}
		s->i++;
	}
}

static int	initialize_values(t_exec *s)
{
	s->i = 0;
	s->has_cmd = 0;
	s->args = malloc(sizeof(char *) * 1024);
	if (!s->args)
		return (1);
	return (0);
}

int	try_to_open_input(t_token *lst)
{
	int	fd;

	fd = open(lst->next->arg, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->next->arg, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	close(fd);
	return (0);
}

char	**build_args_and_advance(t_token **lst, t_data *data)
{
	t_exec	s;

	if (initialize_values(&s))
		return (NULL);
	ft_bzero(s.args, sizeof(char *) * 1024);
	if ((*lst)->type == INPUT && lstsize(*lst) > 2)
		return (managing_input_case(lst, data, &s), free_tab(s.args), NULL);
	else if ((*lst)->type == INPUT && lstsize(*lst) <= 2)
		return (data->exit_code = try_to_open_input(*lst), free_tab(s.args));
	while (*lst && (*lst)->type != PIPE)
	{
		if ((*lst)->type == CMD || (*lst)->type == ARG)
			adding_value(lst, &s, data);
		else if ((*lst)->type == TRUNC || (*lst)->type == APPEND
			|| (*lst)->type == INPUT || (*lst)->type == HEREDOC)
			*lst = (*lst)->next;
		if (*lst)
			*lst = (*lst)->next;
	}
	if (*lst && (*lst)->type == PIPE)
		*lst = (*lst)->next;
	s.args[s.i] = NULL;
	if (!s.has_cmd)
		return (free_tab(s.args), NULL);
	return (s.args);
}
