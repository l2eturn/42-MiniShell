/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:50:26 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/26 18:31:36 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_one(int index, int pipes[MAX_PIPE][2],
	t_cmd_group *cmd_lines, int process_num)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
		exec(index, pipes, cmd_lines, process_num);
	return (pid);
}

static int	fork_all(int pipes[MAX_PIPE][2],
	t_cmd_group *cmd_lines, int process_num)
{
	int	pid[MAX_PROCESS];
	int	i;

	i = 0;
	while (i < process_num)
	{
		pid[i] = exec_one(i, pipes, cmd_lines, process_num);
		i++;
	}
	close_all(pipes, process_num, cmd_lines);
	return (wait_pid_process(pid, process_num, cmd_lines));
}

int	execute_command(t_cmd_group *cmd_lines)
{
	int	pipes[MAX_PIPE][2];
	int	process_num;

	if (!cmd_lines)
		return (0);
	process_num = cmd_len(cmd_lines);
	if (loop_open(cmd_lines) != 0 && !cmd_lines->is_heredoc)
	{
		if (process_num == 1 || g_status == SIGINT)
			return (cmd_lines->exit_status);
	}
	if (process_num == 1 && cmd_lines->cmd
		&& is_builtin(cmd_lines->cmd) && !cmd_lines->is_error)
		return (run_single_builtin(cmd_lines));
	if (open_pipes(pipes, process_num) == -1)
		return (1);
	signal_handler(MAIN_CHILD);
	process_num = fork_all(pipes, cmd_lines, process_num);
	signal_handler(MAIN);
	return (process_num);
}
