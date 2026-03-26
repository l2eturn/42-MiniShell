/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:50:26 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/26 18:25:56 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_not_found(t_cmd_group *cur)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cur && cur->cmd)
		ft_putstr_fd(cur->cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

t_cmd_group	*get_cmd_at(t_cmd_group *cmd_lines, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		cmd_lines = cmd_lines->next;
		i++;
	}
	return (cmd_lines);
}

int	run_single_builtin(t_cmd_group *cmd_lines)
{
	int	i;

	signal_handler(MAIN_CHILD);
	i = execute_builtin(cmd_lines);
	signal_handler(MAIN);
	return (i);
}
