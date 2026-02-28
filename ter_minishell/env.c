/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:53:13 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	env_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	**env_dup(char **envp)
{
	char	**new;
	int		size;
	int		i;

	size = env_size(envp);
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

/*
** ft_getenv: find value of 'name' in envp array
** returns pointer into existing string (do NOT free)
*/
char	*ft_getenv(const char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

/*
** env_set: add or update a KEY=VALUE pair in envp
** frees old envp array (but NOT the old string pointers since they may be args)
** returns new envp
*/
char	**env_set(char **envp, char *arg)
{
	char	**new;
	int		size;
	int		i;
	int		key_len;

	key_len = 0;
	while (arg[key_len] && arg[key_len] != '=')
		key_len++;
	size = env_size(envp);
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(envp[i], arg, key_len) == 0 && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(arg);
			return (envp);
		}
		i++;
	}
	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (envp);
	i = 0;
	while (i < size)
	{
		new[i] = envp[i];
		i++;
	}
	new[i] = ft_strdup(arg);
	new[i + 1] = NULL;
	free(envp);
	return (new);
}

/*
** env_unset: remove KEY from envp, return new envp
*/
char	**env_unset(char **envp, const char *key)
{
	char	**new;
	int		size;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(key);
	size = env_size(envp);
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (envp);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			free(envp[i]);
		else
			new[j++] = envp[i];
		i++;
	}
	new[j] = NULL;
	free(envp);
	return (new);
}
