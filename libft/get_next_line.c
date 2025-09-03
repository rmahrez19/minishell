/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:40:39 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/29 21:29:09 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	resultcheck(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_file(char *result, int fd)
{
	char	*buffer;
	int		bytesread;

	buffer = malloc(5 + 1);
	if (!buffer)
		return (NULL);
	if (!result)
		result = ft_callocgnl(1, 1);
	bytesread = read(fd, buffer, 5);
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		result = ft_strjoingnl(result, buffer);
		if (resultcheck(result))
			break ;
		bytesread = read(fd, buffer, 5);
	}
	free(buffer);
	if ((bytesread == -1 && (!result || *result == '\0')) || (bytesread == 0
			&& (!result || *result == '\0')))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

char	*extractresult(char *result)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!result || !*result)
		return (NULL);
	while (result[i] && result[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	ft_strlcpygnl(str, result, i + 2);
	return (str);
}

void	*free_buffer(char *buffer)
{
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;
	char		*new_buffer;

	if (fd == -42 && buffer)
		return (free_buffer(buffer));
	buffer = read_file(buffer, fd);
	line = extractresult(buffer);
	if (fd < 0 || read(fd, 0, 0) < 0 || !buffer || !line)
		return (NULL);
	temp = ft_strchrgnl(buffer, '\n');
	if (temp)
	{
		new_buffer = malloc(ft_strlengnl(temp + 1) + 1);
		if (!new_buffer)
			return (free_buffer(buffer));
		ft_strlcpygnl(new_buffer, temp + 1, ft_strlengnl(temp + 1) + 1);
	}
	else
		new_buffer = NULL;
	free(buffer);
	buffer = new_buffer;
	return (line);
}
