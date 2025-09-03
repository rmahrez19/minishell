/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:42:25 by lobriott          #+#    #+#             */
/*   Updated: 2025/03/29 21:28:51 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlengnl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	static size_t	capacity;
	char			*new_result;

	capacity = 0;
	if (capacity < ft_strlengnl(s1) + ft_strlengnl(s2) + 1)
	{
		capacity = (ft_strlengnl(s1) + ft_strlengnl(s2) + 1) * 2;
		new_result = malloc(capacity);
		if (!new_result)
		{
			free(s1);
			return (NULL);
		}
		ft_strlcpygnl(new_result, s1, ft_strlengnl(s1) + 1);
		free(s1);
		s1 = new_result;
	}
	ft_strlcpygnl(s1 + ft_strlengnl(s1), s2, ft_strlengnl(s2) + 1);
	return (s1);
}

void	*ft_callocgnl(size_t count, size_t size)
{
	size_t	bytes;
	void	*ptr;
	char	*str;

	bytes = count * size;
	if (size && ((bytes / size) != count))
		return (NULL);
	ptr = malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	str = (char *)ptr;
	if (ptr == NULL)
		return (NULL);
	while (bytes > 0)
	{
		*str = 0;
		str++;
		bytes--;
	}
	return (ptr);
}

char	*ft_strchrgnl(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlcpygnl(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlengnl(src));
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlengnl(src));
}
