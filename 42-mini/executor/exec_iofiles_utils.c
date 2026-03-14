/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iofiles_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:37:29 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/03 21:02:33 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_infiles	*new_infile(char *filename, bool is_h, char *lim)
{
	t_infiles	*new;

	new = ft_safe_calloc(1, sizeof(t_infiles), "");
	if (!new)
		exit_msg("Malloc Err");
	new->filename = filename;
	new->is_heredoc = is_h;
	new->lim = lim;
	new->next = NULL;
	return (new);
}

t_outfiles	*new_outfile(char *filename, bool is_append)
{
	t_outfiles	*new;

	new = ft_safe_calloc(1, sizeof(t_outfiles), "");
	if (!new)
		exit_msg("Malloc Err");
	new->filename = filename;
	new->is_append = is_append;
	new->next = NULL;
	return (new);
}

int	handle_redirection(t_cmd_group *cur)
{
	int	out_status;

	if (first_redirect_is_out(cur))
	{
		out_status = loop_out(cur);
		cur->exit_status = loop_in(cur);
		if (out_status != 0 && cur->exit_status == 0)
			cur->exit_status = out_status;
	}
	else
	{
		cur->exit_status = loop_in(cur);
		if (g_status != SIGINT && cur->exit_status == 0)
			cur->exit_status = loop_out(cur);
	}
	return (cur->exit_status);
}
