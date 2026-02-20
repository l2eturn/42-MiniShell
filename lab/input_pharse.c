/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pharse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 03:00:55 by slimvutt          #+#    #+#             */
/*   Updated: 2026/02/21 03:00:55 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"
#include <stdlib.h>
#include <stdio.h>

static int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\a')
		return (1);
	return (0);
}

static size_t	get_token_len(char *str, size_t i)
{
	size_t	len;
	char	q;

	len = 0;
	q = 0;
	while (str[i + len])
	{
		if ((str[i + len] == '\'' || str[i + len] == '\"') && q == 0)
			q = str[i + len];
		else if (str[i + len] == q)
			q = 0;
		else if (q == 0 && is_space(str[i + len]))
			break ;
		len++;
	}
	return (len);
}

static char	*extract_token(char *str, size_t *i)
{
	size_t	len;
	size_t	j;
	char	*token;

	len = get_token_len(str, *i);
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
	{
		perror("Malloc");
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (j < len)
	{
		token[j] = str[*i + j];
		j++;
	}
	token[len] = '\0';
	*i += len;
	return (token);
}

char	**parse_input(char *input)
{
	char	**tokens;
	size_t	i;
	size_t	pos;

	tokens = malloc(MAX_INPUT * sizeof(char *));
	if (!tokens)
		exit(EXIT_FAILURE);
	i = 0;
	pos = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		tokens[pos] = extract_token(input, &i);
		pos++;
	}
	tokens[pos] = NULL;
	return (tokens);
}

void	free_tokens(char **tokens)
{
	size_t	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
