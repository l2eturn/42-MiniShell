/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 16:06:31 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	sigaction(signum, &sa, NULL);
}

void	signal_handler_heredoc(t_sig_mode mode)
{
	if (mode == HEREDOC)
	{
		set_signal(SIGINT, heredoc_interrupt);
		set_signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == MAIN_HEREDOC)
	{
		set_signal(SIGINT, main_heredoc_interrupt);
		set_signal(SIGQUIT, SIG_IGN);
	}
}

void	print_signal_exit(int status)
{
	if (!WIFSIGNALED(status))
		return ;
	if (WTERMSIG(status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (WTERMSIG(status) == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	else if (WTERMSIG(status) == SIGSEGV)
		ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
}
