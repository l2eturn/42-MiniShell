/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:35:35 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── quote tracking ──────────────────────────────────────────────────────── */

/*
** update_quote_status — toggle in_single / in_double as we walk the token.
**
** Rules:
**   ' toggles in_single only when NOT inside double quotes
**   " toggles in_double only when NOT inside single quotes
*/
static void	update_quote_status(char c, bool *in_single, bool *in_double)
{
	if (c == '\'' && !(*in_double))
		*in_single = !(*in_single);
	if (c == '\"' && !(*in_single))
		*in_double = !(*in_double);
}

/* ── dollar sign handling ────────────────────────────────────────────────── */

/*
** handle_dollar_sign — called when we hit a '$' in the token.
**
** If the next char is not expandable (e.g. "$ " or "$;"),
** treat the '$' as a literal character.
** Otherwise advance past '$' and expand the variable.
*/
static char	*handle_dollar_sign(char *token, int *i, char ***env_ptr,
	t_exp_tmp params)
{
	char	*addition;

	if (!is_expandable_char(token[*i + 1]))
		return (ft_strjoin_char1(ft_strdup(""), token[(*i)++]));
	(*i)++;
	addition = expand_variable(token, i, env_ptr, params);
	return (addition);
}

/* ── single character processing ─────────────────────────────────────────── */

/*
** process_char — handle one character of the token.
**
** Updates quote state, then either:
**   - appends the char literally (not '$')
**   - expands a variable (is '$')
**
** Returns the grown expanded string, or NULL on malloc failure.
*/
static char	*process_char(char *expanded, char *token, int *i,
	t_exp_tmp params)
{
	char	*addition;
	char	*tmp;

	update_quote_status(token[*i], params.in_single, params.in_double);
	if (token[*i] != '$')
	{
		tmp = ft_strjoin_char1(expanded, token[(*i)++]);
		free(expanded);
		return (tmp);
	}
	addition = handle_dollar_sign(token, i, params.env_ptr, params);
	if (addition == NULL)
		return (NULL);
	tmp = ft_strjoin(expanded, addition);
	free(expanded);
	free(addition);
	return (tmp);
}

/* ── public API ──────────────────────────────────────────────────────────── */

/*
** expand_token — expand all $VAR and $? in a single token string.
**
** Walks the token char by char, tracking quote state.
** Inside single quotes: $ is literal.
** Inside double quotes: $ is expanded.
** Outside quotes:       $ is expanded.
**
** Returns a new heap string with expansions applied.
** Quote characters themselves are preserved (parser strips them later).
*/
char	*expand_token(char *token, char ***env_ptr, int *exit_status)
{
	char		*expanded;
	int			i;
	bool		in_single;
	bool		in_double;
	t_exp_tmp	params;

	expanded = ft_strdup("");
	i = 0;
	in_single = false;
	in_double = false;
	params.in_single = &in_single;
	params.in_double = &in_double;
	params.exit_status = exit_status;
	params.env_ptr = env_ptr;
	while (token[i] != '\0')
	{
		expanded = process_char(expanded, token, &i, params);
		if (expanded == NULL)
			return (NULL);
	}
	return (expanded);
}
