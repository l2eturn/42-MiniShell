/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:35:04 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** heredoc_interrupt — SIGINT inside the heredoc child process.
**
** When the user presses ctrl-C while typing heredoc input:
**   1. clear the readline line
**   2. print a newline so the terminal looks clean
**   3. exit(130) — bash convention for SIGINT exit
**
** The parent detects this via WEXITSTATUS == 130 or WIFSIGNALED,
** then sets g_status = SIGINT and stops reading.
*/
void	heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

/*
** main_heredoc_interrupt — SIGINT in the parent while waiting for heredoc child.
**
** The parent must NOT exit here — it needs to waitpid() for the child first.
** Just record the signal; the heredoc() function checks g_status after waitpid.
*/
void	main_heredoc_interrupt(int signum)
{
	(void)signum;
	g_status = SIGINT;
}
