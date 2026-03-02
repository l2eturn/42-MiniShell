/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:12:18 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 15:12:42 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc_token(char *token)
{
	return (token != NULL && ft_strncmp(token, "<<", 3) == 0);
}

bool	is_append_token(char *token)
{
	return (token != NULL && ft_strncmp(token, ">>", 3) == 0);
}

bool	is_simple_redirect(char *token, char c)
{
	return (token != NULL && token[0] == c && token[1] == '\0');
}

bool	is_pipe_token(char *token)
{
	return (token != NULL && ft_strncmp(token, "|", 2) == 0);
}
