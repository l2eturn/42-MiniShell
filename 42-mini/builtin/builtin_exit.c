/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:28:51 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/16 13:53:47 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
static void	builtin_exit_help(t_cmd_group *cmd)
{
	if (cmd->prev == NULL && cmd->next == NULL)
		ft_putendl_fd("exit", STDOUT_FILENO);
}
 
static void	builtin_exit_help_2(t_cmd_group *cmd, char *text)
{
	ft_putstr_fd(text, STDERR_FILENO);
	close_builtin_fds(cmd);
}
 
static void	do_exit(t_cmd_group *cmd, int exit_code)
{
	char	**env;
 
	close_builtin_fds(cmd);
	env = *cmd->env_ptr;
	free_cmd_group(cmd);
	free_env(env);
	rl_clear_history();
	exit(exit_code);
}
 
static bool	is_in_pipe(t_cmd_group *cmd)
{
	return (cmd->prev != NULL || cmd->next != NULL);
}
 
static int	exit_with_arg(t_cmd_group *cmd)
{
	long	exit_code_long;
	int		exit_code;
 
	if (cmd->argv[1][0] == '\x01')
		ft_memmove(cmd->argv[1], cmd->argv[1] + 1, ft_strlen(cmd->argv[1]));
	if (!is_valid_numeric(cmd->argv[1]))
	{
		builtin_exit_help_2(cmd, "exit: numeric argument required\n");
		if (is_in_pipe(cmd))
			return (2);
		do_exit(cmd, 2);
	}
	if (cmd->argv[2] != NULL)
	{
		builtin_exit_help_2(cmd, "exit: too many arguments\n");
		return (1);
	}
	exit_code_long = ft_atol(cmd->argv[1]);
	exit_code = (int)(exit_code_long % 256);
	if (exit_code < 0)
		exit_code += 256;
	if (is_in_pipe(cmd))
		return (exit_code);
	do_exit(cmd, exit_code);
	return (exit_code);
}
 
int	builtin_exit(t_cmd_group *cmd)
{
	builtin_exit_help(cmd);
	if (cmd->argv[1] == NULL || ft_strncmp(cmd->argv[1], "--", 3) == 0)
	{
		if (is_in_pipe(cmd))
			return (get_exit_stats(-1));
		do_exit(cmd, get_exit_stats(-1));
	}
	return (exit_with_arg(cmd));
}


// #include "minishell.h"
 
// static void	builtin_exit_help(t_cmd_group *cmd)
// {
// 	if (cmd->prev == NULL && cmd->next == NULL)
// 		ft_putendl_fd("exit", STDOUT_FILENO);
// }
 
// static void	builtin_exit_help_2(t_cmd_group *cmd, char *text)
// {
// 	ft_putstr_fd(text, STDERR_FILENO);
// 	close_builtin_fds(cmd);
// }
 
// static void	do_exit(t_cmd_group *cmd, int exit_code)
// {
// 	char	**env;
 
// 	close_builtin_fds(cmd);
// 	env = *cmd->env_ptr;
// 	free_cmd_group(cmd);
// 	free_env(env);
// 	rl_clear_history();
// 	exit(exit_code);
// }
 
// int	builtin_exit(t_cmd_group *cmd)
// {
// 	long	exit_code_long;
// 	int		exit_code;
 
// 	builtin_exit_help(cmd);
// 	if (cmd->argv[1] == NULL || ft_strncmp(cmd->argv[1], "--", 3) == 0)
// 		do_exit(cmd, get_exit_stats(-1));
// 	if (cmd->argv[1][0] == '\x01')
// 		ft_memmove(cmd->argv[1], cmd->argv[1] + 1, ft_strlen(cmd->argv[1]));
// 	if (!is_valid_numeric(cmd->argv[1]))
// 	{
// 		builtin_exit_help_2(cmd, "exit: numeric argument required\n");
// 		do_exit(cmd, 2);
// 	}
// 	if (cmd->argv[2] != NULL)
// 	{
// 		builtin_exit_help_2(cmd, "exit: too many arguments\n");
// 		return (1);
// 	}
// 	exit_code_long = ft_atol(cmd->argv[1]);
// 	exit_code = (int)(exit_code_long % 256);
// 	if (exit_code < 0)
// 		exit_code += 256;
// 	do_exit(cmd, exit_code);
// 	return (exit_code);
// }

// #include "minishell.h"

// static void	builtin_exit_help(t_cmd_group *cmd)
// {
// 	if (cmd->prev == NULL && cmd->next == NULL)
// 		ft_putendl_fd("exit", STDOUT_FILENO);
// }

// static void	builtin_exit_help_2(t_cmd_group *cmd, char *text)
// {
// 	ft_putstr_fd(text, STDERR_FILENO);
// 	close_builtin_fds(cmd);
// }

// int	builtin_exit(t_cmd_group *cmd)
// {
// 	long	exit_code_long;
// 	int		exit_code;

// 	builtin_exit_help(cmd);
// 	if (cmd->argv[1] == NULL || ft_strncmp(cmd->argv[1], "--", 3) == 0)
// 		exit_errno(get_exit_stats(-1));
// 	if (cmd->argv[1][0] == '\x01')
// 		ft_memmove(cmd->argv[1], cmd->argv[1] + 1, ft_strlen(cmd->argv[1]));
// 	if (!is_valid_numeric(cmd->argv[1]))
// 	{
// 		builtin_exit_help_2(cmd, "exit: numeric argument required\n");
// 		exit_errno(2);
// 	}
// 	if (cmd->argv[2] != NULL)
// 	{
// 		builtin_exit_help_2(cmd, "exit: too many arguments\n");
// 		return (1);
// 	}
// 	exit_code_long = ft_atol(cmd->argv[1]);
// 	exit_code = (int)(exit_code_long % 256);
// 	if (exit_code < 0)
// 		exit_code += 256;
// 	close_builtin_fds(cmd);
// 	exit_errno(exit_code);
// 	return (exit_code);
// }
