/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 13:46:56 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 14:46:20 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*is_binary_cmd(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	t_exec	s;

	s.path = is_binary_cmd(cmd);
	if (s.path)
		return (s.path);
	s.i = check_path(envp);
	if (!s.i)
		return (NULL);
	s.paths = ft_split(envp[s.i] + 5, ':');
	if (!s.paths)
		return (NULL);
	s.i = -1;
	while (s.paths[++s.i])
	{
		s.part_path = ft_strjoin(s.paths[s.i], "/");
		if (!s.part_path)
			continue ;
		s.path = ft_strjoin_free(s.part_path, cmd);
		if (!s.path)
			continue ;
		if (access(s.path, X_OK) == 0)
			return (free_tab(s.paths), s.path);
		free(s.path);
	}
	return (free_tab(s.paths), NULL);
}

char	*from_char_to_str(char a, char b)
{
	char	*result;

	result = malloc(3);
	if (!result)
		return (NULL);
	result[0] = a;
	result[1] = b;
	result[2] = '\0';
	return (result);
}

char	*manage_question_mark(t_data *data, char *ptr, int i)
{
	char	*temp;
	char	*result;

	(void)i;
	temp = ft_itoa(data->exit_code);
	result = ft_strjoin(ptr, temp);
	free(temp);
	free(ptr);
	return (result);
}

char	*adding_result(char *ptr, char *to_join, int to_free)
{
	char	*result;

	result = ft_strjoin(ptr, to_join);
	if (!result)
		return (NULL);
	if (to_free)
		free(to_join);
	if (ptr)
		free(ptr);
	return (result);
}
