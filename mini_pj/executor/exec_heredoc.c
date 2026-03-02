/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 15:37:29 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_cmd_group *cur)
{
	char	**tmp;
	char	*expanded;
	int		exit_status;

	exit_status = get_exit_stats(-1);
	tmp = ft_calloc(2, sizeof(char *));
	if (!tmp)
		return (ft_strdup(line));
	tmp[0] = ft_strdup(line);
	tmp[1] = NULL;
	expand_tokens(tmp, cur->env_ptr, &exit_status);
	expanded = tmp[0];
	free(tmp);
	return (expanded);
}

static int	process_heredoc_line(char *line, t_cmd_group *cur)
{
	char	*expanded;

	if (ft_strncmp(line, cur->lim, ft_strlen(cur->lim) + 1) == 0)
	{
		free(line);
		return (0);
	}
	expanded = expand_heredoc_line(line, cur);
	write(cur->h_pipe[1], expanded, ft_strlen(expanded));
	write(cur->h_pipe[1], "\n", 1);
	free(expanded);
	free(line);
	return (1);
}

void	read_til_lim(t_cmd_group *cur)
{
	char	*line;

	while (g_status != SIGINT)
	{
		line = readline("> ");
		if (g_status == SIGINT)
		{
			if (line)
				free(line);
			break ;
		}
		if (line == NULL)
		{
			heredoc_eof(cur);
			break ;
		}
		if (!process_heredoc_line(line, cur))
			break ;
	}
}

int	heredoc(t_cmd_group *cur)
{
	int	pid;
	int	exit_status;

	if (pipe(cur->h_pipe) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		signal_handler(HEREDOC);
		read_til_lim(cur);
		exit_errno(0);
	}
	signal_handler(MAIN_HEREDOC);
	close_fd(cur->h_pipe[1]);
	cur->in_fd = cur->h_pipe[0];
	waitpid(pid, &exit_status, 0);
	signal_handler(MAIN);
	if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
		g_status = SIGINT;
	else if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) == 130)
		g_status = SIGINT;
	return (exit_status);
}

void	loop_heredoc(t_cmd_group *cmd_lines)
{
	t_cmd_group	*cur;

	cur = cmd_lines;
	while (cur)
	{
		if (cur->is_heredoc == true)
			heredoc(cur);
		cur = cur->next;
	}
}
