/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 15:49:56 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 13:33:07 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(int pipes[MAX_PIPE][2], int process_num)
{
	int	i;

	i = 0;
	while (i < process_num - 1)
	{
		if (pipe(pipes[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

void	close_pipes(int pipes[MAX_PIPE][2], int process_num)
{
	int	i;

	i = 0;
	while (i < process_num - 1)
	{
		close_fd(pipes[i][0]);
		close_fd(pipes[i][1]);
		i++;
	}
}

void	close_all_fd(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;

	cur = cmd_lines;
	while (cur)
	{
		close_fd(cur->in_fd);
		close_fd(cur->out_fd);
		close_fd(cur->h_pipe[0]);
		close_fd(cur->h_pipe[1]);
		cur = cur->next;
	}
}

void	close_all(int pipes[MAX_PIPE][2], int process_num,
	t_cmd_group *cmd_lines)
{
	close_pipes(pipes, process_num);
	close_all_fd(cmd_lines);
}

void	dup_process(int index, int pipes[MAX_PIPE][2],
	t_cmd_group *cur, int process_num)
{
	if (index == 0 && cur->in_fd != STDIN_FILENO)
		dup2(cur->in_fd, STDIN_FILENO);
	else if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index == process_num - 1 && cur->out_fd != STDOUT_FILENO)
		dup2(cur->out_fd, STDOUT_FILENO);
	else if (index < process_num - 1)
		dup2(pipes[index][1], STDOUT_FILENO);
}
