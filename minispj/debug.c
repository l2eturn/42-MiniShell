/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cduangpl <cduangpl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:26:54 by cduangpl          #+#    #+#             */
/*   Updated: 2026/02/27 14:26:56 by cduangpl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_str_tab(char *label, char **tab)
{
	int	i;

	printf("%s", label);
	if (tab == NULL)
	{
		printf("(null)\n");
		return ;
	}
	i = 0;
	while (tab[i] != NULL)
		printf("[%s] ", tab[i++]);
	printf("\n");
}

void	print_cmd_group(t_cmd_group *g)
{
	t_cmd_group	*curr;
	int			i;

	curr = g;
	i = 0;
	printf("---------------------------\n");
	while (curr != NULL)
	{
		printf("== cmds[%d] ==\n", i);
		printf("cmd: %s\n", curr->cmd);
		print_str_tab("argv: ", curr->argv);
		print_str_tab("in_filenames: ", curr->in_filenames);
		print_str_tab("out_filenames: ", curr->out_filenames);
		printf("operator: %d\n", curr->operator);
		printf("---------------------------\n");
		curr = curr->next;
		i++;
	}
}
