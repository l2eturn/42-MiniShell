/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:58:14 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	ft_env(t_shell *shell)
{
	int	i;

	if (!shell->envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

static void	print_export(char **envp)
{
	int	i;
	int	eq;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		eq = 0;
		while (envp[i][eq] && envp[i][eq] != '=')
			eq++;
		if (envp[i][eq] == '=')
		{
			write(STDOUT_FILENO, envp[i], eq + 1);
			write(STDOUT_FILENO, "\"", 1);
			ft_putstr_fd(&envp[i][eq + 1], STDOUT_FILENO);
			write(STDOUT_FILENO, "\"", 1);
		}
		else
			ft_putstr_fd(envp[i], STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

int	ft_export(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
	{
		print_export(shell->envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		shell->envp = env_set(shell->envp, args[i]);
		i++;
	}
	return (0);
}

int	ft_unset(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		shell->envp = env_unset(shell->envp, args[i]);
		i++;
	}
	return (0);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	code;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!args[1])
		code = shell->exit_status;
	else
		code = ft_atoi(args[1]);
	free_strarr(shell->envp);
	free(shell);
	rl_clear_history();
	exit(code);
	return (0);
}
