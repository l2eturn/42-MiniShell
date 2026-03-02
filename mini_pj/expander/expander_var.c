/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 15:05:35 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── $? handling ─────────────────────────────────────────────────────────── */

/*
** handle_exit_status — expand $? to the last exit code.
**
** Inside single quotes: return literal "$?" string.
** Outside single quotes: return ft_itoa(exit_status).
** Advances *i past the '?' character.
*/
static char	*handle_exit_status(int *i, int *exit_status, bool *in_single)
{
	(*i)++;
	if (!(*in_single))
		return (ft_itoa(*exit_status));
	return (ft_strdup("$?"));
}

/* ── key extraction ──────────────────────────────────────────────────────── */

/*
** extract_key — read the variable name starting at token[*i].
**
** Consumes alphanumeric chars and '_'.
** Advances *i to the first non-key character.
** Returns a heap-allocated copy of the key (may be empty string "").
*/
static char	*extract_key(char *token, int *i)
{
	int		start;
	char	*key;

	start = *i;
	while (token[*i] != '\0' && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	key = ft_substr(token, start, *i - start);
	return (key);
}

/* ── env lookup ──────────────────────────────────────────────────────────── */

/*
** get_var_value — look up key in env and return its value.
**
** Inside single quotes: return "$key" literally ($ was already consumed,
**   so we reconstruct it here to keep the original text).
** Outside single quotes: look up in env, return "" if not found.
*/
static char	*get_var_value(char *key, char ***env_ptr, bool *in_single)
{
	char	*value;
	char	*tmp;

	if (*in_single)
	{
		tmp = ft_strjoin("$", key);
		return (tmp);
	}
	value = ft_getenv(*env_ptr, key);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/* ── public API ──────────────────────────────────────────────────────────── */

/*
** expand_variable — expand the variable starting at token[*i].
**
** Called after '$' has been consumed by the caller.
** Handles:
**   $?        → exit status
**   $VAR      → env lookup
**   $         → literal (empty key → empty string)
**
** Advances *i past the variable name.
** Returns a new heap string with the value (never NULL on success).
*/
char	*expand_variable(char *token, int *i,
	char ***env_ptr, t_exp_tmp params)
{
	char	*key;
	char	*result;

	if (token[*i] == '\0')
		return (ft_strdup(""));
	if (token[*i] == '?')
		return (handle_exit_status(i, params.exit_status, params.in_single));
	key = extract_key(token, i);
	if (key == NULL)
		return (NULL);
	if (key[0] == '\0')
	{
		free(key);
		return (ft_strdup(""));
	}
	result = get_var_value(key, env_ptr, params.in_single);
	free(key);
	return (result);
}
