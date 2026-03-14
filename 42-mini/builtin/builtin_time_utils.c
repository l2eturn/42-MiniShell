/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_time_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 21:08:54 by slimvutt          #+#    #+#             */
/*   Updated: 2026/03/03 21:08:54 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_diff(struct timeval s, struct timeval e, char *label)
{
	long	sec;
	long	usec;

	sec = e.tv_sec - s.tv_sec;
	usec = e.tv_usec - s.tv_usec;
	normalize_tv(&sec, &usec);
	print_time_val(sec, usec, label);
}
