/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:28:32 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/03 02:55:26 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_cmd_group *cmd)
{
	char	cwd[PATH_MAX];
	char	*pwd_env;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, cmd->out_fd);
		close_builtin_fds(cmd);
		return (0);
	}
	pwd_env = ft_getenv(*(cmd->env_ptr), "PWD");
	if (pwd_env)
	{
		ft_putendl_fd(pwd_env, cmd->out_fd);
		close_builtin_fds(cmd);
		return (0);
	}
	perror("pwd");
	close_builtin_fds(cmd);
	return (1);
}
