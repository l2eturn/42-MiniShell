/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 00:00:00 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/03 00:00:00 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	normalize_tv(long *sec, long *usec)
{
	if (*usec < 0)
	{
		(*sec)--;
		*usec += 1000000;
	}
}

static void	print_time_val(long sec, long usec, char *label)
{
	long	min;
	long	rem;
	long	ms;

	min = sec / 60;
	rem = sec % 60;
	ms = usec / 1000;
	ft_putstr_fd(label, STDERR_FILENO);
	ft_putnbr_fd(min, STDERR_FILENO);
	ft_putstr_fd("m", STDERR_FILENO);
	ft_putnbr_fd(rem, STDERR_FILENO);
	ft_putstr_fd(".", STDERR_FILENO);
	if (ms < 100)
		ft_putchar_fd('0', STDERR_FILENO);
	if (ms < 10)
		ft_putchar_fd('0', STDERR_FILENO);
	ft_putnbr_fd(ms, STDERR_FILENO);
	ft_putendl_fd("s", STDERR_FILENO);
}

static void	print_time_result(struct timespec s, struct timespec e,
	struct rusage *rb, struct rusage *ra)
{
	long	ws;
	long	wu;
	long	us;
	long	uu;
	long	ss;
	long	su;

	ws = e.tv_sec - s.tv_sec;
	wu = (e.tv_nsec - s.tv_nsec) / 1000;
	us = ra->ru_utime.tv_sec - rb->ru_utime.tv_sec;
	uu = ra->ru_utime.tv_usec - rb->ru_utime.tv_usec;
	ss = ra->ru_stime.tv_sec - rb->ru_stime.tv_sec;
	su = ra->ru_stime.tv_usec - rb->ru_stime.tv_usec;
	normalize_tv(&ws, &wu);
	normalize_tv(&us, &uu);
	normalize_tv(&ss, &su);
	print_time_val(ws, wu, "real\t");
	print_time_val(us, uu, "user\t");
	print_time_val(ss, su, "sys\t");
}

static int	timed_exec(char *line, char ***env_ptr, int *exit_status)
{
	t_cmd_group	*cmds;

	if (!is_completed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n",
			STDERR_FILENO);
		exit_status_help_process_line(exit_status);
		return (*exit_status);
	}
	if (!is_valid_tokens(line))
	{
		exit_status_help_process_line(exit_status);
		return (*exit_status);
	}
	cmds = init_cmd_group(line, env_ptr, exit_status);
	if (cmds)
	{
		*exit_status = execute_command(cmds);
		get_exit_stats(*exit_status);
		free_cmd_group(cmds);
	}
	return (*exit_status);
}

int	handle_time_keyword(char *line, char ***env_ptr, int *exit_status)
{
	struct timespec	start;
	struct timespec	end;
	struct rusage	rb;
	struct rusage	ra;
	char			*tl;

	tl = line;
	if (ft_strncmp(tl, "time", 4) != 0)
		return (-1);
	tl += 4;
	if (*tl != ' ' && *tl != '\t' && *tl != '\0')
		return (-1);
	while (*tl == ' ' || *tl == '\t')
		tl++;
	clock_gettime(CLOCK_MONOTONIC, &start);
	getrusage(RUSAGE_CHILDREN, &rb);
	timed_exec(tl, env_ptr, exit_status);
	clock_gettime(CLOCK_MONOTONIC, &end);
	getrusage(RUSAGE_CHILDREN, &ra);
	print_time_result(start, end, &rb, &ra);
	return (*exit_status);
}
