/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:50:26 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 16:01:43 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_not_found(t_cmd_group *cur)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cur->cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}

t_cmd_group	*get_cmd_at(t_cmd_group *cmd_lines, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		cmd_lines = cmd_lines->next;
		i++;
	}
	return (cmd_lines);
}

int	run_single_builtin(t_cmd_group *cmd_lines)
{
	int	i;

	signal_handler(MAIN_CHILD);
	i = execute_builtin(cmd_lines);
	signal_handler(MAIN);
	return (i);
}

int	inner_wait_process(int pid[MAX_PROCESS], int process_num,
	t_cmd_group *cmd_lines, int closed_process)
{
	int			status;
	int			exit_status;
	t_cmd_group	*cur;

	exit_status = 0;
	cur = cmd_lines;
	while (closed_process < process_num)
	{
		waitpid(pid[closed_process], &status, 0);
		print_signal_exit(status);
		if (WIFSIGNALED(status))
		{
			g_status = WTERMSIG(status);
			exit_status = 128 + WTERMSIG(status);
		}
		else if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		cur->exit_status = exit_status;
		closed_process++;
		cur = cur->next;
	}
	return (exit_status);
}

int	wait_pid_process(int pid[MAX_PROCESS], int process_num,
	t_cmd_group *cmd_lines)
{
	return (inner_wait_process(pid, process_num, cmd_lines, 0));
}
