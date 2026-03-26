/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 19:24:27 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
