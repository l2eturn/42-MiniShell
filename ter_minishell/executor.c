/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:53:03 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

static void	exec_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = find_path(cmd->args[0], shell->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->args[0], STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->args, shell->envp);
	perror("minishell");
	free(path);
	exit(1);
}

/*
** exec_child: set up pipes + redirections, then exec command
** prev_fd: read end of previous pipe (-1 if first command)
** pfd: current pipe fds (NULL if last command)
*/
void	exec_child(t_cmd *cmd, int prev_fd, int *pfd, t_shell *shell)
{
	setup_signals_child();
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (pfd)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		close(pfd[1]);
	}
	if (setup_redirs(cmd->redirs) < 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exit(run_builtin(cmd, shell));
	exec_external(cmd, shell);
}

/*
** exec_pipeline: fork and execute all commands in the pipeline
** returns exit status of last command
*/
static int	exec_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		prev_fd;
	int		pfd[2];
	pid_t	pid;
	t_cmd	*cur;
	int		status;

	prev_fd = -1;
	cur = cmds;
	status = 0;
	while (cur)
	{
		if (cur->next && pipe(pfd) < 0)
			return (perror("minishell: pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("minishell: fork"), 1);
		if (pid == 0)
			exec_child(cur, prev_fd, cur->next ? pfd : NULL, shell);
		if (prev_fd != -1)
			close(prev_fd);
		if (cur->next)
		{
			close(pfd[1]);
			prev_fd = pfd[0];
		}
		cur = cur->next;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (g_signal == SIGINT)
			return (130);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}

int	execute(t_cmd *cmds, t_shell *shell)
{
	if (!cmds || !cmds->args || !cmds->args[0])
		return (0);
	if (is_single_builtin(cmds))
	{
		if (setup_redirs(cmds->redirs) < 0)
			return (1);
		return (run_builtin(cmds, shell));
	}
	return (exec_pipeline(cmds, shell));
}
