/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 16:19:49 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strncmp("&&", str, 2) == 0)
		return (2);
	if (ft_strncmp("||", str, 2) == 0)
		return (2);
	if (ft_strncmp("<<", str, 2) == 0)
		return (2);
	if (ft_strncmp(">>", str, 2) == 0)
		return (2);
	if (str[0] == '&' || str[0] == '|')
		return (1);
	if (str[0] == '(' || str[0] == ')')
		return (1);
	if (str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}

int	is_fully_quoted(char *src, int len)
{
	char	q;
	int		i;

	if (len < 2)
		return (0);
	if (src[0] != '\'' && src[0] != '"')
		return (0);
	q = src[0];
	i = 1;
	while (i < len)
	{
		if (src[i] == q)
		{
			if (i == len - 1)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}
