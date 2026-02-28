/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:52:48 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myshell.h"

int	g_signal = 0;

static void	run_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(input);
	if (!tokens)
		return ;
	expand_tokens(tokens, shell);
	cmds = parser(tokens);
	free_token_list(tokens);
	if (!cmds)
		return ;
	shell->exit_status = execute(cmds, shell);
	free_cmd_list(cmds);
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		setup_signals();
		input = readline(PROMPT);
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
		if (*input)
			add_history(input);
		run_input(input, shell);
		free(input);
	}
}

static t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		exit(1);
	shell->envp = env_dup(envp);
	shell->exit_status = 0;
	return (shell);
}

static void	cleanup_shell(t_shell *shell)
{
	free_strarr(shell->envp);
	free(shell);
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	shell = init_shell(envp);
	shell_loop(shell);
	cleanup_shell(shell);
	return (0);
}
