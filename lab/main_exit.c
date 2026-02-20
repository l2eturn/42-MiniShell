#include "myshell.h"


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

void	shell_loop(char **envp)
{
	char 	*input;
	size_t	input_size;
	char 	**args;

	input = NULL;
	input_size = 0;

	while (1)
	{
		printf("[nigga_shell👨🏿]> ");
		getline(&input, &input_size, stdin);
		if (is_exit(input))
			exit(EXIT_SUCCESS);
		args = parse_input(input);
		//printf("%s\n", input);
		for (int i = 0; args[i]; i ++){
			printf("This is your %d argument: ",i);
			printf("%s\n", args[i]);
		}
		free_tokens(args);
	}
}

int main(int ac, char **av, char **envp)
{
	shell_loop(envp);
	//printf("%s\n",envp[atoi(av[1])]);
	printf("exit loop");
}
