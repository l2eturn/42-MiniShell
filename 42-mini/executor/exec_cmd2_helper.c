/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:31:01 by slimvutt          #+#    #+#             */
/*   Updated: 2026/03/29 19:51:47 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_exit(t_cmd_group *cmd_lines, char ***env_ptr, int code)
{
	free_cmd_group(cmd_lines);
	free_env(*env_ptr);
	rl_clear_history();
	exit(code);
}

static void	exec_execve(t_cmd_group *cmd_lines, char ***env_ptr,
	char **argv, char *path)
{
	execve(path, argv, *env_ptr);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(argv[0], STDERR_FILENO);
	free(path);
	child_exit(cmd_lines, env_ptr, 126);
}

static void	exec_path(t_cmd_group *cur, t_cmd_group *cmd_lines,
	char ***env_ptr)
{
	char	*path;
	int		ret;

	ft_memmove_argv(cur->argv);
	if (cur->cmd[0] == '\x01')
		ft_memmove(cur->cmd, cur->cmd + 1, ft_strlen(cur->cmd));
	if (is_builtin(cur->cmd))
	{
		ret = execute_builtin(cur);
		child_exit(cmd_lines, env_ptr, ret);
	}
	path = find_cmd(cur->cmd, *env_ptr);
	if (!path)
	{
		exec_cmd_not_found(cur);
		child_exit(cmd_lines, env_ptr, 127);
	}
	exec_execve(cmd_lines, env_ptr, cur->argv, path);
}

void	exec(int index, int pipes[MAX_PIPE][2],
	t_cmd_group *cmd_lines, int process_num)
{
	t_cmd_group	*cur;

	signal_handler(CHILD);
	cur = get_cmd_at(cmd_lines, index);
	dup_process(index, pipes, cur, process_num);
	close_all(pipes, process_num, cmd_lines);

	if (cur->in_fd > 2)
		close(cur->in_fd);
	if (cur->out_fd > 2)
		close(cur->out_fd);

	cur->in_fd = STDIN_FILENO;
	cur->out_fd = STDOUT_FILENO;
	if (cur->is_error)
		child_exit(cmd_lines, cur->env_ptr, 1);
	if (!cur->cmd)
		child_exit(cmd_lines, cur->env_ptr, 0);
	exec_path(cur, cmd_lines, cur->env_ptr);
}
