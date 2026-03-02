/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:59:32 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 15:00:30 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ── lexer utils ─────────────────────────────────────────────────────────── */

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	is_quotation_mark(char c)
{
	return (c == '\'' || c == '"');
}

int	is_special_char(char c)
{
	return (is_whitespace(c) || c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')' || c == '&');
}

/* ── memory utils ────────────────────────────────────────────────────────── */

void	*ft_safe_calloc(size_t count, size_t size, char *msg)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
		exit_msg(msg);
	return (ptr);
}

/* ── string utils ────────────────────────────────────────────────────────── */

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
