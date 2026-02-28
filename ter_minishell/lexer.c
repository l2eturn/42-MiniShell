/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:52:54 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

static t_token	*new_token(char *value, int type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = type;
	tok->next = NULL;
	return (tok);
}

static void	tok_addback(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

/*
** read_word: reads a word token from input[i]
** handles single and double quotes as a unit
** returns new index after the word
*/
static int	read_word(char *input, int i, t_token **lst)
{
	int		start;
	char	q;

	start = i;
	q = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && q == 0)
			q = input[i];
		else if (input[i] == q)
			q = 0;
		else if (!q && (IS_SP(input[i]) || IS_OP(input[i])))
			break ;
		i++;
	}
	tok_addback(lst, new_token(ft_substr(input, start, i - start), TK_WORD));
	return (i);
}

/*
** read_op: reads |, <, >, >>, << tokens
** returns new index after the operator
*/
static int	read_op(char *input, int i, t_token **lst)
{
	if (input[i] == '|')
		tok_addback(lst, new_token(ft_strdup("|"), TK_PIPE));
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		tok_addback(lst, new_token(ft_strdup("<<"), TK_HEREDOC));
		return (i + 2);
	}
	else if (input[i] == '>' && input[i + 1] == '>')
	{
		tok_addback(lst, new_token(ft_strdup(">>"), TK_APPEND));
		return (i + 2);
	}
	else if (input[i] == '<')
		tok_addback(lst, new_token(ft_strdup("<"), TK_IN));
	else if (input[i] == '>')
		tok_addback(lst, new_token(ft_strdup(">"), TK_OUT));
	return (i + 1);
}

t_token	*lexer(char *input)
{
	t_token	*lst;
	int		i;

	if (!input)
		return (NULL);
	lst = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && IS_SP(input[i]))
			i++;
		if (!input[i])
			break ;
		if (IS_OP(input[i]))
			i = read_op(input, i, &lst);
		else
			i = read_word(input, i, &lst);
	}
	return (lst);
}

void	free_token_list(t_token *lst)
{
	t_token	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->value);
		free(lst);
		lst = next;
	}
}
