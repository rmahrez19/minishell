/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:53:18 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/06 13:44:20 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_operator(char *input, int i, t_token **tokens)
{
	int		op_len;
	char	*token_str;
	int		type_token;

	op_len = is_full_operator(input, i);
	type_token = typetoken(input, i);
	token_str = ft_strndup(input + i, op_len);
	ft_lstadd_token_back(tokens, ft_lst_token_new(token_str, type_token, 0, 0));
	return (i + op_len);
}

int	handle_quote(char *input, int i, t_token **tokens)
{
	t_quotes	s;

	s.double_q = 0;
	s.colle_next = 0;
	s.quote = input[i];
	s.start = i++;
	while (input[i] && input[i] != s.quote)
		i++;
	if (input[i] == s.quote)
		i++;
	s.token_str = ft_strndup(input + s.start, i - s.start);
	if (!s.token_str)
		return (i);
	s.type_token = typetoken(s.token_str, 0);
	if (input[i] && input[i] > 32 && !is_operator_char(input[i]))
		s.colle_next = 1;
	ft_lstadd_token_back(tokens,
		ft_lst_token_new(s.token_str, s.type_token, s.double_q, s.colle_next));
	return (i);
}

int	handle_word(char *input, int i, t_token **tokens)
{
	t_parsing	s;

	s.start = i;
	while (is_good_char(input[i], 3))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			s.quote = input[i++];
			while (input[i] && input[i] != s.quote)
				i++;
			if (input[i] == s.quote)
				i++;
		}
		else
			i++;
	}
	s.dup = ft_strndup(input + s.start, i - s.start);
	if (!s.dup)
		return (i);
	s.type_token = typetoken(s.dup, 0);
	s.colle_next = is_good_char(input[i], 2);
	s.new = ft_lst_token_new(s.dup, s.type_token, 0, s.colle_next);
	if (!s.new)
		return (free(s.dup), i);
	return (ft_lstadd_token_back(tokens, s.new), i);
}

int	launch_handle_redirection(char *input, int i,
			t_token **tokens, t_parsing *s)
{
	s->type_token = typetoken(input, i);
	s->token_str = ft_strndup(input + i, s->op_len);
	ft_lstadd_token_back(tokens,
		ft_lst_token_new(s->token_str, s->type_token, 0, 0));
	i += s->op_len;
	while (input[i])
	{
		while (input[i] && input[i] <= 32)
			i++;
		if (!input[i])
			break ;
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			i = handle_redirection(input, i, tokens);
		else if (input[i] == '\'' || input[i] == '"')
			i = handle_quote(input, i, tokens);
		else
			i = handle_word(input, i, tokens);
	}
	return (i);
}

int	handle_redirection(char *input, int i, t_token **tokens)
{
	t_parsing	s;

	s.op_len = 1;
	if ((input[i] == '<' && input[i + 1] == '<')
		|| (input[i] == '>' && input[i + 1] == '>'))
		s.op_len = 2;
	return (launch_handle_redirection(input, i, tokens, &s));
}
