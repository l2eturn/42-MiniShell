/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myshell.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 00:00:00 by student           #+#    #+#             */
/*   Updated: 2026/02/28 08:55:12 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYSHELL_H
# define MYSHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define PROMPT "\x1b[36m[mimikyu_shell⚡]$ \x1b[0m"

# define TK_WORD    0
# define TK_PIPE    1
# define TK_IN      2
# define TK_OUT     3
# define TK_APPEND  4
# define TK_HEREDOC 5

/* Is space macro */
# define IS_SP(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' \
	|| (c) == '\r' || (c) == '\v' || (c) == '\f')

/* Is operator macro */
# define IS_OP(c) ((c) == '|' || (c) == '<' || (c) == '>')

extern int	g_signal;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	**envp;
	int		exit_status;
}	t_shell;

/* main.c */
void	shell_loop(t_shell *shell);

/* lexer.c */
t_token	*lexer(char *input);
void	free_token_list(t_token *lst);

/* parser.c */
t_cmd	*parser(t_token *tokens);
void	free_cmd_list(t_cmd *lst);

/* parser_utils.c */
t_cmd	*new_cmd(void);
t_redir	*new_redir(int type, char *target);
void	redir_addback(t_redir **lst, t_redir *new);
void	cmd_addback(t_cmd **lst, t_cmd *new);
void	free_redir_list(t_redir *lst);

/* expander.c */
void	expand_tokens(t_token *tokens, t_shell *shell);
char	*expand_word(char *word, t_shell *shell);

/* executor.c */
int		execute(t_cmd *cmds, t_shell *shell);
void	exec_child(t_cmd *cmd, int prev_fd, int *pfd, t_shell *shell);

/* executor_utils.c */
char	*find_path(char *cmd, char **envp);
void	free_strarr(char **arr);
int		count_cmds(t_cmd *cmds);
int		is_single_builtin(t_cmd *cmds);

/* redir.c */
int		setup_redirs(t_redir *redirs);
int		do_heredoc(char *delim);

/* builtin.c */
int		is_builtin(char *name);
int		run_builtin(t_cmd *cmd, t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args, t_shell *shell);

/* builtin2.c */
int		ft_env(t_shell *shell);
int		ft_export(char **args, t_shell *shell);
int		ft_unset(char **args, t_shell *shell);
int		ft_exit(char **args, t_shell *shell);

/* env.c */
char	*ft_getenv(const char *name, char **envp);
char	**env_set(char **envp, char *arg);
char	**env_unset(char **envp, const char *key);
char	**env_dup(char **envp);
int		env_size(char **envp);

/* signals.c */
void	setup_signals(void);
void	setup_signals_child(void);

#endif
