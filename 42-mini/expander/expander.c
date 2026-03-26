/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 19:29:32 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_expandable_char(char c)
{
	if (c == '\0')
		return (0);
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

char	*ft_strjoin_char1(char *str, char c)
{
	char	*res;
	int		i;

	res = ft_safe_calloc(ft_strlen(str) + 2, sizeof(char), "");
	i = 0;
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	return (res);
}

static char	*strip_token_quotes(char *token)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

	result = ft_calloc(ft_strlen(token) + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '"')
		{
			quote = token[i++];
			while (token[i] && token[i] != quote)
				result[j++] = token[i++];
			if (token[i] == quote)
				i++;
		}
		else
			result[j++] = token[i++];
	}
	result[j] = '\0';
	return (result);
}

void	strip_quotes(char **tokens)
{
	char	*stripped;
	int		i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		stripped = strip_token_quotes(tokens[i]);
		if (stripped)
		{
			free(tokens[i]);
			tokens[i] = stripped;
		}
		i++;
	}
}

void	expand_tokens(char **tokens, char ***env_ptr, int *exit_status)
{
	int		i;
	char	*expanded;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strchr(tokens[i], '$') != NULL)
		{
			expanded = expand_token(tokens[i], env_ptr, exit_status);
			if (expanded != NULL)
			{
				free(tokens[i]);
				tokens[i] = expanded;
			}
		}
		i++;
	}
}
