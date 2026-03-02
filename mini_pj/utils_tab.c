/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 14:27:19 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── append_tab ──────────────────────────────────────────────────────────── */

/*
** append_tab — append one string to a NULL-terminated char** array.
** If tab is NULL, creates a new array with just str.
** Returns the new (reallocated) array.
*/
char	**append_tab(char **tab, char *str)
{
	char	**new_tab;
	int		len;
	int		i;

	len = tab_len(tab);
	new_tab = ft_calloc(len + 2, sizeof(char *));
	if (!new_tab)
		return (tab);
	i = 0;
	while (i < len)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[len] = ft_strdup(str);
	new_tab[len + 1] = NULL;
	free(tab);
	return (new_tab);
}

/* ── split_tokens ────────────────────────────────────────────────────────── */

/*
** join_segment — join tokens[start..end-1] into one space-separated string.
** Used by split_tokens to reconstruct each pipe segment as a string.
*/
static char	*join_segment(char **tokens, int start, int end)
{
	char	*result;
	char	*tmp;
	int		i;

	result = ft_strdup("");
	i = start;
	while (i < end)
	{
		if (i > start)
		{
			tmp = ft_strjoin(result, " ");
			free(result);
			result = tmp;
		}
		tmp = ft_strjoin(result, tokens[i]);
		free(result);
		result = tmp;
		i++;
	}
	return (result);
}

/*
** split_tokens — split a token array on "|" into an array of segment strings.
**
** Input:  ["echo", "hello", "|", "cat", "-e", NULL]
** Output: ["echo hello", "cat -e", NULL]
**
** The returned strings can then each be re-tokenized by the parser
** to build individual t_cmd_group nodes.
*/
char	**split_tokens(char **tokens)
{
	char	**segments;
	char	*segment;
	int		i;
	int		start;

	if (!tokens)
		return (NULL);
	segments = NULL;
	i = 0;
	start = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strncmp(tokens[i], "|", 2) == 0)
		{
			segment = join_segment(tokens, start, i);
			segments = append_tab(segments, segment);
			free(segment);
			start = i + 1;
		}
		i++;
	}
	segment = join_segment(tokens, start, i);
	segments = append_tab(segments, segment);
	free(segment);
	return (segments);
}
