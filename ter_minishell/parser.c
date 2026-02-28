/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:52:38 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

/*
** count_words: count WORD tokens in current command segment (until PIPE/NULL)
** redir operators consume 2 tokens (operator + its target word)
*/
static int	count_words(t_token *tok)
{
	int	n;

	n = 0;
	while (tok && tok->type != TK_PIPE)
	{
		if (tok->type == TK_WORD)
			n++;
		else
		{
			tok = tok->next;
			if (!tok || tok->type == TK_PIPE)
				break ;
		}
		tok = tok->next;
	}
	return (n);
}

/*
** fill_args: allocate args array and fill it from tokens
** returns pointer to next token after this command segment
*/
static t_token	*fill_args(t_token *tok, t_cmd *cmd, int word_count)
{
	int	i;
	int	rtype;

	cmd->args = malloc(sizeof(char *) * (word_count + 1));
	if (!cmd->args)
		return (NULL);
	i = 0;
	while (tok && tok->type != TK_PIPE)
	{
		if (tok->type == TK_WORD)
			cmd->args[i++] = ft_strdup(tok->value);
		else
		{
			rtype = tok->type;
			tok = tok->next;
			if (tok && tok->type == TK_WORD)
				redir_addback(&cmd->redirs, new_redir(rtype, tok->value));
		}
		tok = tok->next;
	}
	cmd->args[i] = NULL;
	return (tok);
}

/*
** parse_cmd: parse one command segment from token list
** fills args and redirs, returns pointer past the PIPE token
*/
static t_token	*parse_cmd(t_token *tok, t_cmd **cmd_out)
{
	t_cmd		*cmd;
	t_token		*save;
	int			wc;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	save = tok;
	wc = count_words(tok);
	if (wc == 0)
	{
		free(cmd);
		*cmd_out = NULL;
		return (NULL);
	}
	/*
	** We need two passes: count_words then fill_args
	** But fill_args needs both words and redirs in one pass
	** So we use count_words just for malloc, then re-walk for filling
	*/
	tok = fill_args(save, cmd, wc);
	/* skip PIPE token */
	if (tok && tok->type == TK_PIPE)
		tok = tok->next;
	*cmd_out = cmd;
	return (tok);
}

t_cmd	*parser(t_token *tokens)
{
	t_cmd	*lst;
	t_cmd	*cmd;
	t_token	*tok;

	if (!tokens)
		return (NULL);
	lst = NULL;
	tok = tokens;
	while (tok)
	{
		tok = parse_cmd(tok, &cmd);
		if (!cmd)
			break ;
		cmd_addback(&lst, cmd);
	}
	return (lst);
}

void	free_cmd_list(t_cmd *lst)
{
	t_cmd	*next;
	int		i;

	while (lst)
	{
		next = lst->next;
		if (lst->args)
		{
			i = 0;
			while (lst->args[i])
				free(lst->args[i++]);
			free(lst->args);
		}
		free_redir_list(lst->redirs);
		free(lst);
		lst = next;
	}
}
