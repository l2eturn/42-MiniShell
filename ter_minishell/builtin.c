/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:53:33 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	return (!ft_strcmp(name, "echo") || !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd") || !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "export") || !ft_strcmp(name, "unset")
		|| !ft_strcmp(name, "exit"));
}


// is_n_flag: check if string is a valid -n flag (e.g. -n, -nn, -nnn)

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	perror("minishell: pwd");
	return (1);
}

/*
** ft_cd: change directory, update PWD and OLDPWD env vars
*/
int	ft_cd(char **args, t_shell *shell)
{
	char	cwd[4096];
	char	*home;

	if (!args[1])
	{
		home = ft_getenv("HOME", shell->envp);
		if (!home)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return (1);
		}
		args[1] = home;
	}
	if (getcwd(cwd, sizeof(cwd)))
		shell->envp = env_set(shell->envp, ft_strjoin("OLDPWD=", cwd));
	if (chdir(args[1]) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(args[1]);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		shell->envp = env_set(shell->envp, ft_strjoin("PWD=", cwd));
	return (0);
}

int	run_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	name = cmd->args[0];
	if (!ft_strcmp(name, "echo"))
		return (ft_echo(cmd->args));
	if (!ft_strcmp(name, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(name, "cd"))
		return (ft_cd(cmd->args, shell));
	if (!ft_strcmp(name, "env"))
		return (ft_env(shell));
	if (!ft_strcmp(name, "export"))
		return (ft_export(cmd->args, shell));
	if (!ft_strcmp(name, "unset"))
		return (ft_unset(cmd->args, shell));
	if (!ft_strcmp(name, "exit"))
		return (ft_exit(cmd->args, shell));
	return (1);
}
