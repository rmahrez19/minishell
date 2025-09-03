/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramahrez <ramahrez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:52:52 by ramahrez          #+#    #+#             */
/*   Updated: 2025/09/03 19:05:15 by ramahrez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_typetoken_flag(int new)
{
	static int	cmd_flag = 1;

	if (new >= 0)
		cmd_flag = new;
	return (cmd_flag);
}

int	typetoken_suite1(const char *str, int i)
{
	if (str[i] == '&' && str[i + 1] == '&')
		return (get_typetoken_flag(1), AND_IF);
	if (str[i] == '|' && str[i + 1] == '|')
		return (get_typetoken_flag(1), OR_IF);
	if (str[i] == '(')
		return (get_typetoken_flag(1), OPEN_PAR);
	if (str[i] == ')')
		return (get_typetoken_flag(1), CLOSE_PAR);
	return (-1);
}

int	typetoken_suite2(const char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (get_typetoken_flag(0), HEREDOC);
	if (str[i] == '>' && str[i + 1] == '>')
		return (get_typetoken_flag(0), APPEND);
	if (str[i] == '<')
		return (get_typetoken_flag(0), INPUT);
	if (str[i] == '>')
		return (get_typetoken_flag(0), TRUNC);
	if (str[i] == '|')
		return (get_typetoken_flag(1), PIPE);
	return (-1);
}

int	typetoken(const char *str, int i)
{
	int	type;

	if (str[i] == 0)
		return (get_typetoken_flag(1), 0);
	type = typetoken_suite1(str, i);
	if (type != -1)
		return (type);
	type = typetoken_suite2(str, i);
	if (type != -1)
		return (type);
	if (get_typetoken_flag(-1) == 1)
		return (get_typetoken_flag(0), CMD);
	return (ARG);
}
