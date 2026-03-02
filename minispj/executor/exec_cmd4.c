/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 03:00:32 by slimvutt          #+#    #+#             */
/*   Updated: 2026/03/03 03:00:32 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_process_status(t_cmd_group *cur, int status)
{
	print_signal_exit(status);
	if (WIFSIGNALED(status))
	{
		g_status = WTERMSIG(status);
		cur->exit_status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		cur->exit_status = WEXITSTATUS(status);
}

int	inner_wait_process(int pid[MAX_PROCESS], int process_num,
	t_cmd_group *cmd_lines, int closed_process)
{
	int			status;
	int			wpid;
	int			i;
	t_cmd_group	*cur;

	(void)closed_process;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid <= 0)
			break ;
		i = 0;
		cur = cmd_lines;
		while (i < process_num && pid[i] != wpid)
		{
			cur = cur->next;
			i++;
		}
		if (i < process_num)
			set_process_status(cur, status);
	}
	cur = cmd_lines;
	while (cur->next)
		cur = cur->next;
	return (cur->exit_status);
}

int	wait_pid_process(int pid[MAX_PROCESS], int process_num,
	t_cmd_group *cmd_lines)
{
	return (inner_wait_process(pid, process_num, cmd_lines, 0));
}
