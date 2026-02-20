/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 01:34:48 by slimvutt          #+#    #+#             */
/*   Updated: 2026/02/21 01:34:48 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int					command_cd(char **args, char **envp)
{
	(void)envp;
    if (args[1] == NULL)
    {
        fprintf(stderr, "minishell: cd: expected argument\n");
        return (1);
	}
    if (chdir(args[1]) != 0)
    {
        perror("minishell: cd");
        return (1);
    }
    return (0);
}
int					command_pwd(void)
{

}
int					command_echo(char **args, char **envp)
{

}
int					command_env(char **envp)
{

}
int					command_which(char **args, char **envp)
{

}

char				**command_setenv(char **args, char **envp)
{

}
char				**command_unsetenv(char **args, char **envp)
{

}