#ifndef MYSHELL_H
# define MYSHELL_H
# define MAX_INPUT 42

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char				**parse_input(char *input);
void 				free_tokens(char** tokens);
int					shell_builts(char **args, char **envp, char *initial_directory);
int					ft_strcmp(const char *s1, const char *s2);
//Builts-in function
int					command_cd(char **args, char **envp);
int					command_pwd(void);
int					command_echo(char **args, char **envp);
int					command_env(char **envp);
int					command_which(char **args, char **envp);

char				**command_setenv(char **args, char **envp);
char				**command_unsetenv(char **args, char **envp);
#endif
