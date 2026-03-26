/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:35:43 by slimvutt          #+#    #+#             */
/*   Updated: 2026/03/26 18:42:16 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit_help(t_cmd_group *cmd)
{
	if (cmd->prev == NULL && cmd->next == NULL)
		ft_putendl_fd("exit", STDOUT_FILENO);
}

void	do_exit(t_cmd_group *cmd, int exit_code)
{
	char	**env;

	close_builtin_fds(cmd);
	env = *cmd->env_ptr;
	free_cmd_group(cmd);
	free_env(env);
	rl_clear_history();
	exit(exit_code);
}

bool	is_in_pipe(t_cmd_group *cmd)
{
	return (cmd->prev != NULL || cmd->next != NULL);
}

static void	builtin_exit_help_2(t_cmd_group *cmd, char *text)
{
	ft_putstr_fd(text, STDERR_FILENO);
	close_builtin_fds(cmd);
}

int	exit_with_arg(t_cmd_group *cmd)
{
	long	exit_code_long;
	int		exit_code;

	if (cmd->argv[1][0] == '\x01')
		ft_memmove(cmd->argv[1], cmd->argv[1] + 1, ft_strlen(cmd->argv[1]));
	if (!is_valid_numeric(cmd->argv[1]))
	{
		builtin_exit_help_2(cmd, "exit: numeric argument required\n");
		if (is_in_pipe(cmd))
			return (2);
		do_exit(cmd, 2);
	}
	if (cmd->argv[2] != NULL)
	{
		builtin_exit_help_2(cmd, "exit: too many arguments\n");
		return (1);
	}
	exit_code_long = ft_atol(cmd->argv[1]);
	exit_code = (int)(exit_code_long % 256);
	if (exit_code < 0)
		exit_code += 256;
	if (is_in_pipe(cmd))
		return (exit_code);
	do_exit(cmd, exit_code);
	return (exit_code);
}
