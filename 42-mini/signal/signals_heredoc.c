/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/29 20:16:55 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	// exit(130);
	close(STDIN_FILENO);
}

void	main_heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
}
