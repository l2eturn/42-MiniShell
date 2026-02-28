/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:52:57 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

/* IS_VARCHAR: valid characters in a variable name */
# define IS_VARCHAR(c) (((c) >= 'a' && (c) <= 'z') \
	|| ((c) >= 'A' && (c) <= 'Z') \
	|| ((c) >= '0' && (c) <= '9') \
	|| (c) == '_')

/*
** append_str: concatenate str to *result (frees old *result)
*/
static void	append_str(char **result, char *str)
{
	char	*tmp;

	if (!str)
		return ;
	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

/*
** expand_dollar: handle $VAR or $? expansion
** advances *i past the variable reference
** returns newly joined result string
*/
static char	*expand_dollar(char *result, char *word, int *i,
	t_shell *shell)
{
	char	*name;
	char	*val;
	int		len;

	(*i)++;
	if (word[*i] == '?')
	{
		val = ft_itoa(shell->exit_status);
		append_str(&result, val);
		free(val);
		(*i)++;
		return (result);
	}
	len = 0;
	while (word[*i + len] && IS_VARCHAR(word[*i + len]))
		len++;
	if (len == 0)
	{
		append_str(&result, "$");
		return (result);
	}
	name = ft_substr(word, *i, len);
	val = ft_getenv(name, shell->envp);
	free(name);
	append_str(&result, val ? val : "");
	*i += len;
	return (result);
}

/*
** expand_word: process a raw token string
** strips quotes, expands $ (respecting quote context)
** returns a newly allocated expanded string
*/
char	*expand_word(char *word, t_shell *shell)
{
	char	*result;
	char	buf[2];
	int		i;
	char	q;

	result = ft_strdup("");
	i = 0;
	q = 0;
	while (word[i])
	{
		if (word[i] == '\'' && q == 0)
		{
			q = '\'';
			i++;
		}
		else if (word[i] == '\'' && q == '\'')
		{
			q = 0;
			i++;
		}
		else if (word[i] == '"' && q == 0)
		{
			q = '"';
			i++;
		}
		else if (word[i] == '"' && q == '"')
		{
			q = 0;
			i++;
		}
		else if (word[i] == '$' && q != '\'')
			result = expand_dollar(result, word, &i, shell);
		else
		{
			buf[0] = word[i++];
			buf[1] = '\0';
			append_str(&result, buf);
		}
	}
	return (result);
}

/*
** expand_tokens: expand all WORD tokens in the list in-place
*/
void	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*tok;
	char	*expanded;

	tok = tokens;
	while (tok)
	{
		if (tok->type == TK_WORD)
		{
			expanded = expand_word(tok->value, shell);
			free(tok->value);
			tok->value = expanded;
		}
		tok = tok->next;
	}
}
