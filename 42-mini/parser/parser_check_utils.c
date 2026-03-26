/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 19:29:53 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
