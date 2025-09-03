/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:14:05 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 21:32:19 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_handler(int signum)
{
	(void)signum;
	if (singleton(-1))
	{
		g_code_signaux = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	block_signal(t_data *data)
{
	(void)data;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals_to_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	init_code_signaux(t_data *data)
{
	data->exit_code = g_code_signaux;
	g_code_signaux = 0;
}

// void reset_signals_to_sleep(void)
// {
// 	signal(SIGQUIT, SIG_IGN);
// }