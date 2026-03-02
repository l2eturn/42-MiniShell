/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:38:30 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── redirect classification ─────────────────────────────────────────────── */

bool	is_redirect(char *str)
{
	if (is_simple_redirect(str, '<'))
		return (true);
	if (is_simple_redirect(str, '>'))
		return (true);
	if (is_append_token(str))
		return (true);
	if (is_heredoc_token(str))
		return (true);
	return (false);
}

/* ── pipe validation ─────────────────────────────────────────────────────── */

/*
** is_valid_pipes — returns false if pipe is in an invalid position.
** Invalid: at start, after another pipe, after a redirect, or at end.
*/
bool	is_valid_pipes(char **tokens, int i)
{
	if (ft_strncmp(tokens[i], "|", 2) == 0)
	{
		if (i == 0 || is_pipe_token(tokens[i - 1])
			|| is_append_token(tokens[i - 1])
			|| is_heredoc_token(tokens[i - 1])
			|| is_simple_redirect(tokens[i - 1], '<')
			|| is_simple_redirect(tokens[i - 1], '>')
			|| !tokens[i + 1])
			return (false);
	}
	return (true);
}

/* ── redirect validation ─────────────────────────────────────────────────── */

/*
** is_valid_redirect — returns false if redirect has no valid target.
** Invalid: redirect at end, or followed by another operator.
*/
bool	is_valid_redirect(char **tokens, int i)
{
	if (is_redirect(tokens[i]))
	{
		if (!tokens[i + 1] || is_pipe_token(tokens[i + 1])
			|| is_append_token(tokens[i + 1])
			|| is_heredoc_token(tokens[i + 1])
			|| is_simple_redirect(tokens[i + 1], '<')
			|| is_simple_redirect(tokens[i + 1], '>'))
			return (false);
	}
	return (true);
}

/* ── error printing ──────────────────────────────────────────────────────── */

void	put_err_parese_redirect(char *tokens)
{
	if (!tokens)
	{
		ft_putendl_fd("`newline'", 2);
		return ;
	}
	ft_putstr_fd("'", 2);
	ft_putstr_fd(tokens, 2);
	ft_putendl_fd("'", 2);
}

/* ── no-print validation (used for pipe completion check) ────────────────── */

bool	is_valid_tokens_np(char *line)
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
		if (!is_valid_pipes(tokens, i) || !is_valid_redirect(tokens, i))
		{
			free_tab(tokens);
			return (false);
		}
	}
	free_tab(tokens);
	return (true);
}
