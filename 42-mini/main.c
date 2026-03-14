/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/07 17:09:30 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(char *line, char ***env_ptr, int *exit_status)
{
	t_cmd_group	*cmds;

	if (!is_completed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n",
			STDERR_FILENO);
		exit_status_help_process_line(exit_status);
	}
	else if (!is_valid_tokens(line))
		exit_status_help_process_line(exit_status);
	else
	{
		cmds = init_cmd_group(line, env_ptr, exit_status);
		if (cmds)
		{
			*exit_status = execute_command(cmds);
			if (*exit_status == 130)
				g_status = SIGINT;
			get_exit_stats(*exit_status);
			free_cmd_group(cmds);
		}
	}
}

static int	handle_line(char *line, char ***env_ptr, int exit_status)
{
	if (g_status == SIGINT)
	{
		exit_status = 130;
		get_exit_stats(exit_status);
	}
	if (*line)
	{
		add_history(line);
		if (handle_time_keyword(line, env_ptr, &exit_status) == -1)
			process_line(line, env_ptr, &exit_status);
	}
	free(line);
	return (exit_status);
}

static int	run_shell(char ***env_ptr)
{
	char	*line;
	int		exit_status;

	exit_status = 0;
	signal_handler(MAIN);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		exit_status = handle_line(line, env_ptr, exit_status);
	}
	if (g_status == SIGINT)
		return (130);
	return (exit_status);
}

static char	**init_env(char **envp)
{
	char	**env;
	int		i;

	env = NULL;
	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	char	***env_ptr;
	int		exit_code;

	if (argc > 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		return (127);
	}
	(void)argc;
	(void)argv;
	env = init_env(envp);
	env_ptr = &env;
	set_shlvl(env_ptr);
	exit_code = run_shell(env_ptr);
	cleanup_shell(NULL, env);
	return (exit_code);
}
