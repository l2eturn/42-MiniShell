/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 16:26:13 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_token(char **tokens, int i)
{
	if (!is_valid_pipes(tokens, i))
	{
		ft_putendl_fd("syntax error near unexpected token `|'", 2);
		return (false);
	}
	if (!is_valid_redirect(tokens, i))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
		put_err_parese_redirect(tokens[i + 1]);
		return (false);
	}
	return (true);
}

bool	is_valid_tokens(char *line)
{
	char	**tokens;
	int		i;
	int		tok_len;

	if (line == NULL)
		return (false);
	tokens = tokenizer(line);
	i = -1;
	tok_len = tab_len(tokens);
	while (++i < tok_len)
	{
		if (!check_token(tokens, i))
		{
			free_tab(tokens);
			return (false);
		}
	}
	free_tab(tokens);
	return (true);
}

char	*clean_token(char *token)
{
	if (token && token[0] == '\x01')
		return (token + 1);
	return (token);
}
