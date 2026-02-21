#include "myshell.h"
#include <readline/readline.h>
#include <readline/history.h>
//#include "libft.h"

// Shell loop
// Input Parsing
// Command execution 
// Handle Built-in commands exp. cd, pwd, echo, env, setenv, unsetenv, which, exit
// Execute external commands
// Manage environment variables
// Manage Path
// Error Handling

int	ft_strlen(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len);
}

int is_exit(char **args)
{
    if (!args || !args[0])
        return (0);
    if (ft_strcmp(args[0], "exit") == 0)
        return (1);
    return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	shell_builts(char **args, char **envp)
{
	if (!ft_strcmp(args[0], "cd"))
		command_cd(args, envp);
	else if (!ft_strcmp(args[0], "pwd"))
		command_pwd();
	else if (!ft_strcmp(args[0], "echo"))
		command_echo(args, envp);
	else if (!ft_strcmp(args[0], "env"))
		command_env(envp);
	return (0);
}

void	shell_loop(char **envp)
{
	char	*input;
	char	**args;

	while (1)
	{
		input = readline("[nig_shell👨🏿]> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);

		args = parse_input(input);

		if (args && args[0])
		{
			// --- Debug Token (ลบได้) ---
			for (int i = 0; args[i]; i++)
			{
				printf("This is your %d argument: %s\n", i, args[i]);
			}
			// ------------------------------------------------
			if (is_exit(args))
			{
				free_tokens(args);
				free(input);
				break ;
			}
			shell_builts(args, envp);
		}
		free_tokens(args);
		free(input);
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	
	shell_loop(envp);
	printf("exit loop\n");
	return (0);
}