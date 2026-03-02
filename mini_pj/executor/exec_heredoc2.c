/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 15:37:17 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 15:44:11 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_eof(t_cmd_group *cur)
{
	ft_putstr_fd("minishell: warning: here-document delimited", STDERR_FILENO);
	ft_putstr_fd(" by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(cur->lim, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}
