/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:34:01 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:34:02 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_cmd_group *cmd)
{
	int		i;
	char	**env;

	i = 0;
	env = *(cmd->env_ptr);
	while (env[i] != NULL)
	{
		if (ft_strchr(env[i], '=') != NULL)
			ft_putendl_fd(env[i], cmd->out_fd);
		i++;
	}
	close_builtin_fds(cmd);
	return (0);
}
