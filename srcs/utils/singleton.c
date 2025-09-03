/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 14:45:54 by ramahrez          #+#    #+#             */
/*   Updated: 2025/08/05 21:32:11 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	singleton_heredoc(int value)
{
	static int	ret_value = 0;

	if (value != -1)
		ret_value = value;
	return (ret_value);
}

int	singleton(int value)
{
	static int	ret_val = 0;

	if (value != -1)
		ret_val = value;
	return (ret_val);
}
