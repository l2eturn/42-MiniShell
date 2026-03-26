/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 19:27:53 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_echo_flag(char *arg)
{
	if (!arg || arg[0] == '\x01')
		return (0);
	return (is_valid_echo_flag(arg));
}

static char	*echo_str(char *arg)
{
	if (arg && arg[0] == '\x01')
		return (arg + 1);
	return (arg);
}

static void	print_echo_args(t_cmd_group *cmd, int i, bool newline, int fd)
{
	while (cmd->argv[i] != NULL)
	{
		if (!newline && is_echo_flag(cmd->argv[i]))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(echo_str(cmd->argv[i]), fd);
		if (cmd->argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
}

int	builtin_echo(t_cmd_group *cmd)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (cmd->argv[i] && is_echo_flag(cmd->argv[i]))
	{
		newline = false;
		i++;
	}
	print_echo_args(cmd, i, newline, cmd->out_fd);
	if (newline)
		ft_putstr_fd("\n", cmd->out_fd);
	close_builtin_fds(cmd);
	return (0);
}
