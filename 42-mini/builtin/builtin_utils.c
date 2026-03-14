/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:46:22 by cduangpl          #+#    #+#             */
/*   Updated: 2026/03/02 15:06:01 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_identifier(char *arg)
{
	int	idx;

	if (arg == NULL || arg[0] == '\0' || arg[0] == '=' || ft_isdigit(arg[0]))
		return (false);
	idx = 0;
	while (arg[idx] != '\0' && arg[idx] != '=')
	{
		if (!ft_isalnum(arg[idx]) && arg[idx] != '_')
			return (false);
		idx++;
	}
	return (true);
}

int	find_env_index(char **env, char *arg)
{
	int	idx;
	int	key_len;

	key_len = 0;
	while (arg[key_len] != '\0' && arg[key_len] != '=')
		key_len++;
	idx = 0;
	while (env != NULL && env[idx] != NULL)
	{
		if (ft_strncmp(env[idx], arg, key_len) == 0
			&& (env[idx][key_len] == '=' || env[idx][key_len] == '\0'))
			return (idx);
		idx++;
	}
	return (-1);
}

int	append_env(char ***env, char *arg)
{
	char	**new_env;
	char	**old_env;
	int		size;
	int		i;

	size = tab_len(*env);
	new_env = ft_safe_calloc(size + 2, sizeof(char *), "");
	if (new_env == NULL)
		return (1);
	i = 0;
	while (i < size)
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	if (new_env[i] == NULL)
		return (1);
	new_env[i + 1] = NULL;
	old_env = *env;
	*env = new_env;
	free(old_env);
	return (0);
}

int	set_env_var(char ***env, char *arg)
{
	int		idx;
	char	*dup;
	char	*old;

	idx = find_env_index(*env, arg);
	if (idx >= 0)
	{
		dup = ft_strdup(arg);
		if (dup == NULL)
			return (1);
		old = (*env)[idx];
		(*env)[idx] = dup;
		free(old);
		return (0);
	}
	return (append_env(env, arg));
}

void	inner_unset(char *cur, char ***env_ptr)
{
	int		i;
	int		env_len;
	int		arg_len;
	char	*to_free;

	i = -1;
	arg_len = ft_strlen(cur);
	env_len = tab_len(*env_ptr);
	while (++i < env_len)
	{
		if (ft_strncmp((*env_ptr)[i], cur, arg_len) == 0
			&& (int)ft_strlen((*env_ptr)[i]) >= arg_len)
		{
			to_free = (*env_ptr)[i];
			if (i == env_len - 1)
				(*env_ptr)[i] = NULL;
			else
				ft_memmove(&(*env_ptr)[i], &(*env_ptr)[i + 1],
					(env_len - i) * sizeof(char *));
			free(to_free);
			break ;
		}
	}
}
