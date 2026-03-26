/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 18:22:09 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_infiles(t_infiles *head)
{
	t_infiles	*current;
	t_infiles	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static void	free_outfiles(t_outfiles *head)
{
	t_outfiles	*current;
	t_outfiles	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static void	free_cmd_node(t_cmd_group *node)
{
	if (node == NULL)
		return ;
	free(node->cmds_str);
	node->cmds_str = NULL;
	free_tab(node->cmd_tokens);
	node->cmd_tokens = NULL;
	free_tab(node->in_filenames);
	node->in_filenames = NULL;
	free_tab(node->out_filenames);
	node->out_filenames = NULL;
	free(node->cmd);
	node->cmd = NULL;
	free_tab(node->argv);
	node->argv = NULL;
	free_infiles(node->in_files);
	node->in_files = NULL;
	free_outfiles(node->out_files);
	node->out_files = NULL;
}

void	free_cmd_group(t_cmd_group *cmd_group)
{
	t_cmd_group	*current;
	t_cmd_group	*next;

	current = cmd_group;
	while (current != NULL)
	{
		next = current->next;
		free_cmd_node(current);
		current = next;
	}
	free(cmd_group);
}
