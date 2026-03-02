/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iofiles_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:37:29 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:37:31 by cduangpl         ###   ########.fr       */
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
