/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 19:27:45 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_builtin_fds(t_cmd_group *cmd)
{
	close_fd(cmd->in_fd);
	close_fd(cmd->out_fd);
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
}

int	is_builtin(char *cmd)
{
	if (cmd == NULL)
		return (0);
	return (ft_strncmp(cmd, "echo", 255) == 0
		|| ft_strncmp(cmd, "cd", 255) == 0
		|| ft_strncmp(cmd, "pwd", 255) == 0
		|| ft_strncmp(cmd, "exit", 255) == 0
		|| ft_strncmp(cmd, "env", 255) == 0
		|| ft_strncmp(cmd, "export", 255) == 0
		|| ft_strncmp(cmd, "unset", 255) == 0);
}

int	execute_builtin(t_cmd_group *cmd)
{
	if (cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL)
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 255) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "cd", 255) == 0)
		return (builtin_cd(cmd));
	if (ft_strncmp(cmd->argv[0], "pwd", 255) == 0)
		return (builtin_pwd(cmd));
	if (ft_strncmp(cmd->argv[0], "exit", 255) == 0)
		return (builtin_exit(cmd));
	if (ft_strncmp(cmd->argv[0], "env", 255) == 0)
		return (builtin_env(cmd));
	if (ft_strncmp(cmd->argv[0], "export", 255) == 0)
		return (builtin_export(cmd, cmd->env_ptr));
	if (ft_strncmp(cmd->argv[0], "unset", 255) == 0)
		return (builtin_unset(cmd, cmd->env_ptr));
	return (1);
}

int	execute_builtin_main(t_cmd_group *cmd)
{
	if (cmd == NULL || cmd->argv == NULL || cmd->argv[0] == NULL)
		return (1);
	if (ft_strncmp(cmd->argv[0], "echo", 255) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "cd", 255) == 0)
		return (builtin_cd(cmd));
	if (ft_strncmp(cmd->argv[0], "pwd", 255) == 0)
		return (builtin_pwd(cmd));
	if (ft_strncmp(cmd->argv[0], "exit", 255) == 0)
		return (builtin_exit(cmd));
	if (ft_strncmp(cmd->argv[0], "env", 255) == 0)
		return (builtin_env(cmd));
	if (ft_strncmp(cmd->argv[0], "export", 255) == 0)
		return (builtin_export(cmd, cmd->env_ptr));
	if (ft_strncmp(cmd->argv[0], "unset", 255) == 0)
		return (builtin_unset(cmd, cmd->env_ptr));
	return (1);
}
