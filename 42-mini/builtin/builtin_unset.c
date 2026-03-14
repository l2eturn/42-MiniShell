/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:29:08 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:29:09 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_cmd_group *cmd, char ***env_ptr)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		inner_unset(cmd->argv[i], env_ptr);
		i++;
	}
	close_builtin_fds(cmd);
	return (0);
}
