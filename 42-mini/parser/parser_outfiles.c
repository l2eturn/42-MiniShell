/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_outfiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/14 20:03:30 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_outfiles	*find_last_outfile(t_outfiles *head)
{
	t_outfiles	*curr;

	if (head == NULL)
		return (NULL);
	curr = head;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

static void	add_outfile_to_list(t_cmd_group *node, char *filename,
	bool is_append)
{
	t_outfiles	*new_file;
	t_outfiles	*last;

	new_file = new_outfile(filename, is_append);
	if (node->out_files == NULL)
		node->out_files = new_file;
	else
	{
		last = find_last_outfile(node->out_files);
		last->next = new_file;
	}
}

/* ── redirect processing ─────────────────────────────────────────────────── */

static int	process_output_redirect(t_cmd_group *node, char **tokens, int i)
{
	if (tokens[i + 1] == NULL)
		return (i + 1);
	if (is_append_token(tokens[i]))
	{
		add_outfile_to_list(node, clean_token(tokens[i + 1]), true);
		return (i + 2);
	}
	else if (is_simple_redirect(tokens[i], '>'))
	{
		add_outfile_to_list(node, clean_token(tokens[i + 1]), false);
		return (i + 2);
	}
	return (i + 1);
}

void	set_out_files(t_cmd_group *node)
{
	int	i;

	i = 0;
	while (node->cmd_tokens != NULL && node->cmd_tokens[i] != NULL)
	{
		if (is_append_token(node->cmd_tokens[i])
			|| is_simple_redirect(node->cmd_tokens[i], '>'))
			i = process_output_redirect(node, node->cmd_tokens, i);
		else
			i++;
	}
}
