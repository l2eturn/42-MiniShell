#ifndef MYSHELL_H
# define MYSHELL_H
# define MAX_INPUT 42
#include <stdio.h>
#include <stdlib.h>


char				**parse_input(char *input);
void 				free_tokens(char** tokens);
#endif