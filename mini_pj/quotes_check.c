/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/02/27 13:08:44 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** is_completed_quotes — return true if all quotes in line are closed.
**
** Walks the string tracking open quote state:
**   - single quote: everything until next ' is literal
**   - double quote: everything until next " closes it
**
** Returns true  if no unclosed quotes remain.
** Returns false if a quote was opened but never closed.
*/
bool	is_completed_quotes(char *line)
{
	int		i;
	char	open_quote;

	if (!line)
		return (true);
	i = 0;
	open_quote = 0;
	while (line[i])
	{
		if (open_quote == 0)
		{
			if (line[i] == '\'' || line[i] == '"')
				open_quote = line[i];
		}
		else if (line[i] == open_quote)
			open_quote = 0;
		i++;
	}
	return (open_quote == 0);
}
