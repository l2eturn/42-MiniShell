/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:28:21 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_pwd(char ***env_ptr)
{
	char	cwd[PATH_MAX];
	char	*entry;

	if (!getcwd(cwd, sizeof(cwd)))
		return (0);
	entry = ft_strjoin("PWD=", cwd);
	if (!entry)
		return (0);
	set_env_var(env_ptr, entry);
	free(entry);
	return (1);
}

int	update_oldpwd(char ***env_ptr, const char *saved_pwd)
{
	char	*old_entry;

	if (!saved_pwd || !saved_pwd[0])
		return (0);
	old_entry = ft_strjoin("OLDPWD=", saved_pwd);
	if (!old_entry)
		return (0);
	set_env_var(env_ptr, old_entry);
	free(old_entry);
	return (1);
}

static char	*resolve_path(const char *path, const char *oldpwd,
				const char *home, int fd)
{
	if (path[0] == '-' && path[1] == '\0')
	{
		ft_putendl_fd((char *)oldpwd, fd);
		return (ft_strdup(oldpwd));
	}
	if (path[0] == '~')
	{
		if (!home)
			return (NULL);
		return (ft_strjoin(home, &path[1]));
	}
	return (ft_strdup(path));
}

static int	handle_cd(t_cmd_group *cmd, const char *path,
				const char *oldpwd, int fd)
{
	char	*home;
	char	*resolved;
	char	saved_pwd[PATH_MAX];

	home = ft_getenv(*(cmd->env_ptr), "HOME");
	if (!home && path[0] == '~')
		return (ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO), 1);
	if (!getcwd(saved_pwd, sizeof(saved_pwd)))
		saved_pwd[0] = '\0';
	resolved = resolve_path(path, oldpwd, home, fd);
	if (!resolved)
		return (1);
	if (chdir(resolved) != 0)
	{
		free(resolved);
		perror("cd");
		return (1);
	}
	free(resolved);
	update_oldpwd(cmd->env_ptr, saved_pwd);
	update_pwd(cmd->env_ptr);
	return (0);
}

int	builtin_cd(t_cmd_group *cmd)
{
	char	*path;
	char	*oldpwd;
	int		status;

	if (tab_len(cmd->argv) > 2)
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO), 1);
	if (cmd->argv[1] == NULL)
	{
		path = ft_getenv(*(cmd->env_ptr), "HOME");
		if (path == NULL)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			close_builtin_fds(cmd);
			return (1);
		}
	}
	else
		path = cmd->argv[1];
	oldpwd = ft_getenv(*(cmd->env_ptr), "OLDPWD");
	status = handle_cd(cmd, path, oldpwd, cmd->out_fd);
	close_builtin_fds(cmd);
	return (status);
}
