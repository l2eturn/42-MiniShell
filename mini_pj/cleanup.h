/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/02 14:01:29 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "minishell.h"

/*
** Main cleanup functions
*/

void	free_cmd_group(t_cmd_group *cmd_group);
void	free_env(char **env);
void	cleanup_shell(t_cmd_group *cmd_group, char **env);
void	cleanup_error(t_cmd_group *cmd_group);
void	free_tokens_only(char **tokens);
void	free_segments(char **segments);

#endif
