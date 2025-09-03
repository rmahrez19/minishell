/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: lobriott <loubriottet@student.42.fr>       +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/07/11 22:55:42 by lobriott          #+#    #+#             */
/*   Updated: 2025/07/12 21:05:00 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		g_code_signaux = 0;

void	minishell_loop(char *line, t_token *lst, t_data data)
{
	while (1)
	{
		singleton(1);
		line = readline(CYAN_CLAIR "➜  minishell " RESET);
		if (!line)
		{
			exit(0);
		}
		singleton(0);
		add_history(line);
		lst = ft_parsing(line);
		if (!lst)
			continue ;
		fix_cmd_typing(lst);
		data.lst = lst;
		data.start = lst;
		data.bad_fd = 0;
		if (g_code_signaux)
			init_code_signaux(&data);
		exec(lst, &data);
	}
}
// ft_print_lst_token(lst);
//a ajouter avant exec pour voir le contenu des tokens

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	t_token	*lst;

	line = NULL;
	lst = NULL;
	if (argc == 1 && argv)
	{
		data.env_tab = duplicate_envp(envp, NULL);
		update_shlvl(&data.env_tab, &data);
		data.exit_code = 0;
		block_signal(&data);
		minishell_loop(line, lst, data);
	}
	return (ft_printf("exit\n"), free_tab(data.env_tab), 0);
}
