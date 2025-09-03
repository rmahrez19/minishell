/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_pid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:11:13 by ramahrez          #+#    #+#             */
/*   Updated: 2025/08/12 18:14:46 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	read_pid_from_proc(void)
{
	int		fd;
	char	buf[64];
	ssize_t	n;
	int		i;
	int		pid;

	i = 0;
	pid = 0;
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n <= 0)
		return (-1);
	buf[n] = '\0';
	while (i < n && buf[i] >= '0' && buf[i] <= '9')
	{
		pid = pid * 10 + (buf[i] - '0');
		i++;
	}
	if (i == 0)
		return (-1);
	else
		return (pid);
}

int	add_pid_from_proc(t_exec *s)
{
	int		pid;
	char	*pid_str;

	pid = read_pid_from_proc();
	if (pid < 0)
		return (free(s->temp), 1);
	pid_str = ft_itoa(pid);
	if (!pid_str)
		return (free(s->temp), 1);
	s->temp = adding_result(s->result, pid_str, 0);
	free(pid_str);
	s->i += 2;
	return (0);
}
