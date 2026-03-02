/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:28:51 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:28:54 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(t_cmd_group *cmd)
{
	long	exit_code_long;
	int		exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd->argv[1] == NULL || ft_strncmp(cmd->argv[1], "--", 3) == 0)
		exit_errno(get_exit_stats(-1));
	if (!is_valid_numeric(cmd->argv[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		close_builtin_fds(cmd);
		exit_errno(2);
	}
	if (cmd->argv[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		close_builtin_fds(cmd);
		return (1);
	}
	exit_code_long = ft_atol(cmd->argv[1]);
	exit_code = (int)(exit_code_long % 256);
	if (exit_code < 0)
		exit_code += 256;
	close_builtin_fds(cmd);
	exit_errno(exit_code);
	return (exit_code);
}
