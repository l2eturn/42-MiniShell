#include "myshell.h"
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
		len ++;
	return len;
}

int is_exit(char *str)
{
    char *ext = "exit";
    int i = 0;

    if (!str)
        return 0;
    while (ext[i])
    {
        if (str[i] != ext[i])
            return 0;
        i++;
    }
    if (str[i] == '\0' || str[i] == '\n')
        return 1;  
    return 0;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i ++;
	}
	return (0);
}

// cd, pwd, echo, setenv, unsetenv, which, exit
int	shell_builts(char **args, char **envp, char *initial_directory)
{
	if (!ft_strcmp(args[0],"cd"))
		command_cd(args, envp);
	else if (!ft_strcmp(args[0],"pwd"))
		printf("%s\n", initial_directory);
	return 0;
}

void	shell_loop(char **envp)
{
	char 	*input;
	size_t	input_size;
	char 	**args;
	char	*initial_directory = getcwd(NULL, 0);

	input = NULL;
	input_size = 0;
	while (1)
	{
		printf("[nig_shell👨🏿]> ");
		getline(&input, &input_size, stdin);
		if (is_exit(input))
		{
			free_tokens(args);
			exit(EXIT_SUCCESS);
		}
		//////printf("%s\n", input);
		args = parse_input(input);
		for (int i = 0; args[i]; i ++){
			printf("This is your %d argument: ",i);
			printf("%s\n", args[i]);
		}
		if (args[0] != NULL)
		{
			shell_builts(args, envp, initial_directory);
		}
	}	
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	shell_loop(envp);
	//printf("%s\n",envp[atoi(av[1])]);
	printf("exit loop");
}
