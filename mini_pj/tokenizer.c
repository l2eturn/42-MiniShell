/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 16:18:59 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_len(char *str)
{
	char	open;
	int		len;

	len = is_token(str);
	if (len != 0)
		return (len);
	len = 0;
	while (str[len] != '\0' && !is_special_char(str[len]))
	{
		if (is_quotation_mark(str[len]))
		{
			open = str[len];
			len++;
			while (str[len] != '\0' && str[len] != open)
				len++;
			if (str[len] == open)
				len++;
		}
		else
			len++;
	}
	return (len);
}

static int	count_words(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_whitespace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		cnt++;
		i += token_len(&str[i]);
	}
	return (cnt);
}

static void	fill_str(char *dst, char *src, int len, int quoted)
{
	int	i;
	int	j;

	j = 0;
	if (quoted)
		dst[j++] = '\x01';
	i = 0;
	while (i < len)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
}

static int	fill_tab(char **tab, char *str, int size)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	while (++i < size)
	{
		while (str[j] != '\0' && is_whitespace(str[j]))
			j++;
		len = token_len(&str[j]);
		tab[i] = ft_safe_calloc(len + 1 + is_fully_quoted(&str[j], len),
				sizeof(char), "");
		if (tab[i] == NULL)
			return (0);
		fill_str(tab[i], &str[j], len, is_fully_quoted(&str[j], len));
		j += len;
	}
	return (1);
}

char	**tokenizer(char *str)
{
	int		size;
	char	**tab;

	size = count_words(str);
	tab = ft_safe_calloc(size + 1, sizeof(char *), "");
	if (tab == NULL)
		return (NULL);
	tab[size] = NULL;
	if (!fill_tab(tab, str, size))
		return (NULL);
	return (tab);
}
