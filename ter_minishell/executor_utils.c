/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:53:09 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

void	free_strarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

/*
** find_path: search for cmd in PATH directories
** if cmd contains '/', treat as direct path
** returns malloc'd full path or NULL if not found
*/
char	*find_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths;
	char	*tmp;
	char	*full;
	int		i;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = ft_getenv("PATH", envp);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
		{
			free_strarr(paths);
			return (full);
		}
		free(full);
		i++;
	}
	free_strarr(paths);
	return (NULL);
}

int	count_cmds(t_cmd *cmds)
{
	int		n;
	t_cmd	*cur;

	n = 0;
	cur = cmds;
	while (cur)
	{
		n++;
		cur = cur->next;
	}
	return (n);
}

/*
** is_single_builtin: true if only 1 cmd and it's a builtin
** these run in parent process to affect shell state
*/
int	is_single_builtin(t_cmd *cmds)
{
	if (!cmds || cmds->next)
		return (0);
	if (!cmds->args || !cmds->args[0])
		return (0);
	return (is_builtin(cmds->args[0]));
}
