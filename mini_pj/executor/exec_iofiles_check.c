/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_iofiles_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:37:36 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── access checks ───────────────────────────────────────────────────────── */

int	check_in_access(char *filename, t_cmd_group *cur)
{
	if (!filename)
		return (0);
	if (access(filename, F_OK) == -1)
	{
		fd_error_once(filename, cur, ": No such file or directory");
		return (-1);
	}
	if (access(filename, F_OK | R_OK) == -1)
	{
		fd_error_once(filename, cur, ": Permission denied");
		return (-1);
	}
	return (0);
}

int	check_out_access(char *filename, t_cmd_group *cur)
{
	if (!filename)
	{
		fd_error_once(filename, cur, ": Permission denied");
		return (-1);
	}
	if (access(filename, W_OK) == -1)
	{
		fd_error_once(filename, cur, ": Permission denied");
		return (-1);
	}
	return (0);
}

/* ── error printing ──────────────────────────────────────────────────────── */

void	fd_error_once(char *filename, t_cmd_group *cur, char *msg)
{
	if (!cur->is_error)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
}

/* ── fd cleanup ──────────────────────────────────────────────────────────── */

void	close_old(t_cmd_group *cur)
{
	close_fd(cur->in_fd);
	close_fd(cur->h_pipe[1]);
	close_fd(cur->h_pipe[0]);
}
