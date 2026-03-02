/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iofiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:37:24 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── input redirect opener ───────────────────────────────────────────────── */

static int	inner_loop_in(t_cmd_group *cur, t_infiles *cur_in)
{
	close_old(cur);
	if (check_in_access(cur_in->filename, cur) == -1)
		cur->is_error = true;
	else if (cur_in->is_heredoc)
	{
		cur->is_heredoc = true;
		cur->lim = cur_in->lim;
		if (heredoc(cur) != 0)
		{
			cur->is_error = true;
			return (130);
		}
	}
	else
	{
		cur->is_heredoc = false;
		cur->in_fd = open(cur_in->filename, O_RDONLY);
	}
	return (0);
}

int	loop_in(t_cmd_group *cur)
{
	t_infiles	*cur_in;

	cur_in = cur->in_files;
	if (!cur_in)
		return (0);
	while (cur_in && g_status != SIGINT)
	{
		if (inner_loop_in(cur, cur_in) == 130)
			return (130);
		cur_in = cur_in->next;
	}
	cur_in = cur->in_files;
	while (cur_in->next)
		cur_in = cur_in->next;
	return (cur->is_error);
}

/* ── output redirect opener ──────────────────────────────────────────────── */

int	loop_out(t_cmd_group *cur)
{
	t_outfiles	*cur_out;

	cur_out = cur->out_files;
	if (!cur_out)
		return (0);
	while (cur_out && g_status != SIGINT)
	{
		close_fd(cur->out_fd);
		if (cur_out->is_append)
			cur->out_fd = open(cur_out->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			cur->out_fd = open(cur_out->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cur->out_fd == -1)
		{
			check_out_access(cur_out->filename, cur);
			cur->is_error = true;
			return (1);
		}
		cur_out = cur_out->next;
	}
	return (0);
}

/* ── open all redirects in pipeline ─────────────────────────────────────── */

/*
** loop_open — open all in/out redirects for every node in the pipeline.
** Returns the exit status of the last node.
*/
int	loop_open(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;

	cur = cmd_lines;
	while (cur && g_status != SIGINT)
	{
		cur->exit_status = loop_in(cur);
		if (g_status == SIGINT)
			return (cur->exit_status);
		if (cur->exit_status == 0)
			cur->exit_status = loop_out(cur);
		cur = cur->next;
	}
	cur = cmd_lines;
	while (cur->next)
		cur = cur->next;
	return (cur->exit_status);
}
