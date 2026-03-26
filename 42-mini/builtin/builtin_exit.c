/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:28:51 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/26 18:41:22 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_cmd_group *cmd)
{
	builtin_exit_help(cmd);
	if (cmd->argv[1] == NULL || ft_strncmp(cmd->argv[1], "--", 3) == 0)
	{
		if (is_in_pipe(cmd))
			return (get_exit_stats(-1));
		do_exit(cmd, get_exit_stats(-1));
	}
	return (exit_with_arg(cmd));
}
