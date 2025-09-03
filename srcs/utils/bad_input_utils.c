/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad_input_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 23:06:16 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/12 20:16:31 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strisspace(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	has_invalid_patterns(char *line, t_data *data)
{
	if (!ft_strncmp(line, "\\n", 3) || !ft_strncmp(line, "\\t", 3))
	{
		data->exit_code = 0;
		return (1);
	}
	if (!ft_strncmp(line, ":", 2))
	{
		data->exit_code = 0;
		return (1);
	}
	if (!ft_strncmp(line, "!", 2))
	{
		data->exit_code = 1;
		return (1);
	}
	if (ft_strnstr(line, "<<<", ft_strlen(line))
		|| ft_strnstr(line, ">>>", ft_strlen(line))
		|| ft_strnstr(line, "><", ft_strlen(line))
		|| ft_strnstr(line, "<>", ft_strlen(line))
		|| ft_strnstr(line, "<<<<", ft_strlen(line))
		|| ft_strnstr(line, ">>>>", ft_strlen(line)))
		return (data->exit_code = 2, 2);
	return (0);
}

int	print_syntax_error(char *l, t_data *data)
{
	t_utils	s;

	s.i = 0;
	while (l[s.i] && (l[s.i] == ' ' || (l[s.i] >= 9 && l[s.i] <= 13)))
		s.i++;
	s.start = s.i;
	if (!l[s.i] || !ft_strcmp(l, "<>"))
		return (print_unexpected("newline"), data->exit_code = 2, 1);
	if (l[s.i] == '<' || l[s.i] == '>')
	{
		if (l[s.i + 1] == l[s.i])
			s.i += 2;
		else
			s.i += 1;
	}
	else if (l[s.i] == '|')
		s.i++;
	else
	{
		while (l[s.i] && !(l[s.i] == ' ' || l[s.i] == '|'
				|| l[s.i] == '<' || l[s.i] == '>'))
			s.i++;
	}
	s.len = s.i - s.start;
	return (print_unexpected(l + s.i + 1), data->exit_code = 2, 1);
}

int	ft_is_invalid_input(char *line, t_data *data)
{
	int		status;
	char	*tmp;

	tmp = line;
	line = ft_replace_line(line);
	if (!line || line[0] == '\0' || ft_strisspace(line))
		return (1);
	status = has_invalid_patterns(line, data);
	if (status == 1)
	{
		line = tmp;
		return (1);
	}
	if (status == 2)
	{
		line = tmp;
		return (print_syntax_error(line, data), data->exit_code = 2, 2);
	}
	line = tmp;
	return (0);
}

void	print_invalid_file(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
	free(str);
}
