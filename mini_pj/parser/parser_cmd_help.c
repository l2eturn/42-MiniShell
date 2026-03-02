/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:20:20 by slimvutt          #+#    #+#             */
/*   Updated: 2026/03/02 15:20:20 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_cmd_node_help(t_cmd_group *node, char ***env_ptr)
{
	node->env_ptr = env_ptr;
	node->is_heredoc = false;
	node->lim = NULL;
	node->in_files = NULL;
	node->out_files = NULL;
	node->is_error = false;
	node->exit_status = 0;
}
