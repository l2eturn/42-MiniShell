/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:07:29 by slimvutt          #+#    #+#             */
/*   Updated: 2026/03/02 15:07:29 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
