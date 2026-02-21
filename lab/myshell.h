#ifndef MYSHELL_H
# define MYSHELL_H
# define MAX_INPUT 42

# define COLOR_RED     "\x1b[31m"
# define COLOR_GREEN   "\x1b[32m"
# define COLOR_YELLOW  "\x1b[33m"
# define COLOR_BLUE    "\x1b[34m"
# define COLOR_MAGENTA "\x1b[35m"
# define COLOR_CYAN    "\x1b[36m"
# define COLOR_RESET   "\x1b[0m"
# define COLOR_BLACK   "\x1b[0;30m"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char				**parse_input(char *input);
void 				free_tokens(char** tokens);
int					shell_builts(char **args, char **envp);
int					ft_strcmp(const char *s1, const char *s2);
void				ultimate_freeing(char **args, char *input);
//Builts-in function
int					command_cd(char **args, char **envp);
int					command_pwd(void);
int					command_echo(char **args, char **envp);
int					command_env(char **envp);
int					command_which(char **args, char **envp);

char				**command_setenv(char **args, char **envp);
char				**command_unsetenv(char **args, char **envp);
#endif
