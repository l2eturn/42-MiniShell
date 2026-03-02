/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/02 14:01:26 by slimvutt         ###   ########.fr       */
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

void	free_env(char **env)
{
	int	i;

	if (env == NULL)
		return ;
	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	cleanup_shell(t_cmd_group *cmd_group, char **env)
{
	if (cmd_group != NULL)
		free_cmd_group(cmd_group);
	if (env != NULL)
		free_env(env);
	rl_clear_history();
}

void	cleanup_error(t_cmd_group *cmd_group)
{
	if (cmd_group != NULL)
		free_cmd_group(cmd_group);
}

void	free_tokens_only(char **tokens)
{
	if (tokens != NULL)
		free_tab(tokens);
}

void	free_segments(char **segments)
{
	if (segments != NULL)
		free_tab(segments);
}
