/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:59:48 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	do_heredoc(char *delim)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) < 0)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("\nminishell: warning: heredoc delimited by EOF\n",
				STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

static int	apply_redir(t_redir *r)
{
	int	fd;
	int	flags;

	if (r->type == TK_HEREDOC)
	{
		fd = do_heredoc(r->target);
		if (fd < 0)
			return (-1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (0);
	}
	if (r->type == TK_IN)
		flags = O_RDONLY;
	else if (r->type == TK_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(r->target, flags, 0644);
	if (fd < 0)
	{
		perror(r->target);
		return (-1);
	}
	if (r->type == TK_IN)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	setup_redirs(t_redir *redirs)
{
	t_redir	*r;

	r = redirs;
	while (r)
	{
		if (apply_redir(r) < 0)
			return (-1);
		r = r->next;
	}
	return (0);
}
