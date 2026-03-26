/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 19:31:02 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_shlvl(char ***env_ptr)
{
	char	*shlvl;
	char	*num;
	char	*entry;
	int		lvl;

	shlvl = ft_getenv(*env_ptr, "SHLVL");
	if (shlvl)
		lvl = ft_atoi(shlvl) + 1;
	else
		lvl = 1;
	num = ft_itoa(lvl);
	entry = ft_strjoin("SHLVL=", num);
	free(num);
	set_env_var(env_ptr, entry);
	free(entry);
}
