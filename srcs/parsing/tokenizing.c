/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lobriott <lobriott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:27:29 by lobriott          #+#    #+#             */
/*   Updated: 2025/08/05 20:27:27 by lobriott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tokenize_dispatcher(char *input, int i, t_token **tokens)
{
	while (input[i] && input[i] <= 32)
		i++;
	if (!input[i])
		return (i);
	if (is_operator_char(input[i]))
		return (handle_operator(input, i, tokens));
	else if (input[i] == '\'' || input[i] == '"')
		return (handle_quote(input, i, tokens));
	else if (input[i] == '<' || input[i] == '>')
		return (handle_redirection(input, i, tokens));
	else
		return (handle_word(input, i, tokens));
}

void	adjust_heredoc_limiters(t_token *tokens)
{
	t_token	*curr;

	curr = tokens;
	while (curr && curr->next)
	{
		if (curr->type == HEREDOC && curr->next->type == ARG)
			curr->next->type = LIMITER;
		curr = curr->next;
	}
}

t_token	*ft_tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	if (!check_quotes_closed(input))
		return (ft_putendl_fd("Erreur : quote non fermee", 2), NULL);
	tokens = NULL;
	i = 0;
	while (input[i])
		i = tokenize_dispatcher(input, i, &tokens);
	typetoken("\0", 0);
	if (tokens)
	{
		adjust_heredoc_limiters(tokens);
		tokens->original_string = NULL;
	}
	return (tokens);
}
