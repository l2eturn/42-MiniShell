/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:29:17 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:29:23 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	if (env == NULL || key == NULL || key[0] == '\0')
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=')
				return (&env[i][key_len + 1]);
			else if (env[i][key_len] == '\0')
				return ("");
		}
		i++;
	}
	return (NULL);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env != NULL && env[i] != NULL)
	{
		j = i + 1;
		while (env[j] != NULL)
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_formatted_env(char *entry, int fd)
{
	int	i;

	ft_putstr_fd("declare -x ", fd);
	i = 0;
	while (entry[i] != '\0' && entry[i] != '=')
	{
		ft_putchar_fd(entry[i], fd);
		i++;
	}
	if (entry[i] == '\0')
	{
		ft_putchar_fd('\n', fd);
		return ;
	}
	ft_putstr_fd("=\"", fd);
	i++;
	while (entry[i] != '\0')
	{
		if (entry[i] == '\"' || entry[i] == '\\')
			ft_putchar_fd('\\', fd);
		ft_putchar_fd(entry[i], fd);
		i++;
	}
	ft_putstr_fd("\"\n", fd);
}

void	print_env(char **env, int fd)
{
	int		i;
	char	**sorted;

	sorted = copy_tab(env);
	if (sorted == NULL)
		return ;
	sort_env(sorted);
	i = 0;
	while (sorted[i] != NULL)
	{
		print_formatted_env(sorted[i], fd);
		i++;
	}
}
