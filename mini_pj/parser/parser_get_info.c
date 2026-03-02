/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 16:26:54 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_after_redirect(char **tab, int index)
{
	if (tab == NULL || tab[index] == NULL)
		return (index + 1);
	if (is_heredoc_token(tab[index]) || is_append_token(tab[index])
		|| is_simple_redirect(tab[index], '<')
		|| is_simple_redirect(tab[index], '>'))
	{
		if (tab[index + 1] != NULL)
			return (index + 2);
		return (index + 1);
	}
	return (index + 1);
}

char	**get_in_filenames(char **tab)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (tab != NULL && tab[i] != NULL)
	{
		if (is_simple_redirect(tab[i], '<') && tab[i + 1] != NULL)
			res = append_tab(res, clean_token(tab[i + 1]));
		i = next_after_redirect(tab, i);
	}
	return (res);
}

char	**get_out_filenames(char **tab)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (tab != NULL && tab[i] != NULL)
	{
		if ((is_append_token(tab[i]) || is_simple_redirect(tab[i], '>'))
			&& tab[i + 1] != NULL)
			res = append_tab(res, clean_token(tab[i + 1]));
		i = next_after_redirect(tab, i);
	}
	return (res);
}

char	*get_cmd(char **tab)
{
	if (tab == NULL || tab[0] == NULL)
		return (NULL);
	return (ft_strdup(clean_token(tab[0])));
}

char	**get_argv(char **tab)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	while (tab != NULL && tab[i] != NULL)
	{
		if (is_heredoc_token(tab[i]) || is_append_token(tab[i])
			|| is_simple_redirect(tab[i], '<')
			|| is_simple_redirect(tab[i], '>'))
			i = next_after_redirect(tab, i);
		else
		{
			res = append_tab(res, tab[i]);
			i++;
		}
	}
	return (res);
}
