/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:58:14 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:58:17 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (1);
}

static int	export_without_value(char *arg, char ***env_ptr)
{
	if (find_env_index(*env_ptr, arg) != -1)
		return (0);
	if (append_env(env_ptr, arg) != 0)
		return (-1);
	return (0);
}

static int	handle_export_arg(char *arg, char ***env_ptr)
{
	if (!is_valid_identifier(arg))
		return (export_error(arg));
	if (ft_strchr(arg, '=') != NULL)
	{
		if (set_env_var(env_ptr, arg) != 0)
			return (-1);
		return (0);
	}
	return (export_without_value(arg, env_ptr));
}

static int	process_export_args(t_cmd_group *cmd, char ***env_ptr)
{
	int	i;
	int	status;
	int	result;

	i = 1;
	status = 0;
	while (cmd->argv[i] != NULL)
	{
		result = handle_export_arg(cmd->argv[i], env_ptr);
		if (result == -1)
		{
			close_builtin_fds(cmd);
			return (-1);
		}
		if (result > 0)
			status = result;
		i++;
	}
	return (status);
}

int	builtin_export(t_cmd_group *cmd, char ***env_ptr)
{
	int	status;

	if (cmd->argv[1] == NULL)
	{
		print_env(*env_ptr, cmd->out_fd);
		close_builtin_fds(cmd);
		return (0);
	}
	status = process_export_args(cmd, env_ptr);
	if (status == -1)
		return (1);
	close_builtin_fds(cmd);
	return (status);
}
