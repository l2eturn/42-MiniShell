/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:47:28 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 16:10:34 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_echo_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (false);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

bool	is_valid_numeric(char *str)
{
	int	i;
	int	digit_count;

	if (str == NULL || *str == '\0')
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (false);
	digit_count = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		digit_count++;
		i++;
	}
	if (digit_count > 19)
		return (false);
	return (true);
}

int	get_exit_stats(int exit_status)
{
	static int	g_exit_status = 0;

	if (exit_status < 0)
		return (g_exit_status);
	g_exit_status = exit_status;
	return (g_exit_status);
}

void	ft_memmove_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '\x01')
			ft_memmove(argv[i], argv[i] + 1, ft_strlen(argv[i]));
		i++;
	}
}
