/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/14 20:03:23 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

void	main_heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
}
