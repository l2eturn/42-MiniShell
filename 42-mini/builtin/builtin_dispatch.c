/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:33:41 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── fd cleanup ──────────────────────────────────────────────────────────── */

void	close_builtin_fds(t_cmd_group *cmd)
{
	close_fd(cmd->in_fd);
	close_fd(cmd->out_fd);
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
}

/* ── is_builtin ──────────────────────────────────────────────────────────── */

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

/* ── execute_builtin (in child process / pipeline) ───────────────────────── */
/*
** execute_builtin — dispatch to the correct builtin.
** Called inside a forked child — exit() is safe here.
** cd/export/unset changes do NOT affect the parent shell.
*/
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

/* ── execute_builtin_main (in parent process) ────────────────────────────── */
/*
** execute_builtin_main — dispatch to the correct builtin.
** Called in the PARENT process for single commands (no pipe).
** This means:
**   - cd    actually changes the shell's directory
**   - export/unset actually modify the shell's env
**   - exit  actually exits the shell process
**   - echo/pwd/env behave the same as in child
*/
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
