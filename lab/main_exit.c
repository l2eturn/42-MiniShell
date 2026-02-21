#include "myshell.h"

#include "libft.h"

// Shell loop
// Input Parsing
// Command execution 
// Handle Built-in commands exp. cd, pwd, echo, env, setenv, unsetenv, which, exit
// Execute external commands
// Manage environment variables
// Manage Path
// Error Handling

//int	ft_strlen(char *str)
//{
//	int len = 0;
//	while (str[len])
//		len++;
//	return (len);
//}


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
	else if (!ft_strcmp(args[0], "which"))
		command_env(envp);
	return (0);
}

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		// เช็คว่าชื่อตรงไหม และตัวถัดไปต้องเป็น '=' (เพื่อกันกรณีหา "USER" แต่ไปเจอ "USER_NAME=...")
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (&envp[i][len + 1]);
		// รีเทิร์น Address ของตัวอักษรหลังเครื่องหมาย '='
		i++;
	}
	return (NULL); // ถ้าหาไม่เจอ ให้คืนค่า NULL
}

void	ultimate_freeing(char **args, char *input)
{
	free_tokens(args);
	free(input);
}
// ตัวแปร Environment จะประกอบด้วย ตัวอักษร, ตัวเลข และ _
int env_name_len(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || 
            (str[i] >= 'A' && str[i] <= 'Z') || 
            (str[i] >= '0' && str[i] <= '9') || 
            (str[i] == '_'))
        {
            i++;
        }
        else
            break;
    }
    return (i);
}
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

// eg; echo "Hello $USER"
char    *dolla_2_string(char *str, char **envp)
{
    int     i;
    int     len;
    char    *prefix, *name, *value, *suffix;
    char    *temp, *result;
    char    *raw_env;

    i = 0;
    while (str[i] && str[i] != '$')
        i++;
    if (str[i] != '$' || str[i + 1] == '\0' || str[i + 1] == ' ')
        return (ft_strdup(str));
    prefix = ft_substr(str, 0, i);
    len = env_name_len(&str[i + 1]); 
    name = ft_substr(str, i + 1, len);
    raw_env = ft_getenv(name, envp);
    if (raw_env)
        value = ft_strdup(raw_env);
    else
        value = ft_strdup("");
    suffix = ft_strdup(&str[i + 1 + len]);
    temp = ft_strjoin(prefix, value);
    result = ft_strjoin(temp, suffix);
    free(prefix);
    free(name);
    free(value);
    free(suffix);
    free(temp);
    return (result);
}
void	expand_args(char **args, char **envp)
{
	int		i;
	char	*expand_str;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '$') != NULL)
		{
			expand_str = dolla_2_string(args[i], envp);
			free(args[i]);
			args[i] = expand_str;
		}
		i ++;
	}
}

void	shell_loop(char **envp)
{
	char	*input;
	char	**args;

	while (1)
	{
		input = readline(COLOR_CYAN"[👨🏿 nigga_shell]> "COLOR_RESET);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		args = parse_input(input);
		if (args && args[0])
		{
			if (is_exit(args))
			{
				ultimate_freeing(args, input);
				break ;
			}
			expand_args(args, envp);
			shell_builts(args, envp);
		}
		ultimate_freeing(args, input);
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
