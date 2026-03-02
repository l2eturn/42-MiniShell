/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:28:01 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** exit_msg — print a message to stderr and exit with code 1.
** Used for fatal errors (malloc failure, etc).
*/
void	exit_msg(char *msg)
{
	if (msg && *msg)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	exit(1);
}

/*
** exit_cmd — print "minishell: cmd: err_msg" to stderr, then exit.
** Used when a command itself causes a fatal error.
*/
void	exit_cmd(char *cmd, char *err_msg, int exit_status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (err_msg)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	exit(exit_status);
}

/*
** exit_errno — exit with the given status code.
** Call after a syscall failure when the caller already printed the error.
*/
void	exit_errno(int exit_status)
{
	exit(exit_status);
}
