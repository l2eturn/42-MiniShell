/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 16:06:04 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

static void	handle_main_sigint(int signum)
{
	(void)signum;
	g_status = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_child_sigint(int signum)
{
	(void)signum;
	g_status = SIGINT;
}

static void	handle_child_sigquit(int signum)
{
	(void)signum;
	g_status = SIGQUIT;
}

static void	set_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	sigaction(signum, &sa, NULL);
}

void	signal_handler(t_sig_mode mode)
{
	g_status = 0;
	if (mode == MAIN)
	{
		set_signal(SIGINT, handle_main_sigint);
		set_signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		set_signal(SIGINT, SIG_DFL);
		set_signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == MAIN_CHILD)
	{
		set_signal(SIGINT, handle_child_sigint);
		set_signal(SIGQUIT, handle_child_sigquit);
	}
	else
		signal_handler_heredoc(mode);
}
