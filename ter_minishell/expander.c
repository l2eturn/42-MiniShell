/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:59:07 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

# define IS_VARCHAR(c) (((c) >= 'a' && (c) <= 'z') \
	|| ((c) >= 'A' && (c) <= 'Z') \
	|| ((c) >= '0' && (c) <= '9') \
	|| (c) == '_')

static void	append_str(char **result, char *str)
{
	char	*tmp;

	if (!str)
		return ;
	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

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
