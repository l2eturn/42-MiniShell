#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft/libft.h"

# ifndef HOSTNAME
#  define HOSTNAME "host"
# endif

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define _POSIX_C_SOURCE 200809L

extern volatile sig_atomic_t	g_status;

typedef enum s_sig_mode
{
	MAIN,
	CHILD,
	MAIN_CHILD,
	HEREDOC,
	MAIN_HEREDOC
}	t_sig_mode;

typedef struct s_exp_tmp
{
	int		*exit_status;
	char	***env_ptr;
	bool	*in_single;
	bool	*in_double;
}	t_exp_tmp;

typedef struct s_cmd_group
{
	char			*cmd;           // command name e.g. "echo"
	char			**argv;         // argument vector e.g. ["echo", "hello", NULL]
	char			**in_filenames; // raw input redirect filenames  ["file.txt", NULL]
	char			**out_filenames;// raw output redirect filenames ["out.txt", NULL]
	char			***env_ptr;     // pointer to the env array
	int				in_fd;         // active input fd  (default STDIN_FILENO)
	int				out_fd;        // active output fd (default STDOUT_FILENO)
	int				operator;      // pipe/redirect operator type
	bool			is_heredoc;    // true if input is a heredoc
	char			*lim;          // heredoc delimiter e.g. "EOF"
	int				h_pipe[2];     // heredoc pipe fds
	void			*in_files;     // parsed input file list  (t_file *)
	void			*out_files;    // parsed output file list (t_file *)
	struct s_cmd_group	*next;     // next command in pipeline
	struct s_cmd_group	*prev;     // previous command in pipeline
}	t_cmd_group;

// ===== main.c =====
int			main(int argc, char **argv, char **envp);
char		*ft_getenv(char *name, char **envp);
void		free_tokens(char **tokens);
// ===== main_exit.c =====
void		exit_msg(char *msg);
void		exit_cmd(char *cmd, char *err_msg, int exit_status);
void		exit_errno(int exit_status);

// ===== input_pharse.c =====
char		*get_prompt(char ***env_ptr);
char		*reader(char ***env_ptr);

// ===== builtin/builtin_dispatch.c =====
void		close_builtin_fds(t_cmd_group *cmd);
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd_group *cmd);

// ===== builtin/builtin_cd.c =====
int			builtin_cd(t_cmd_group *cmd);

// ===== builtin/builtin_echo.c =====
int			builtin_echo(t_cmd_group *cmd);

// ===== builtin/builtin_env.c =====
int			builtin_env(t_cmd_group *cmd);

// ===== builtin/builtin_exit.c =====
int			builtin_exit(t_cmd_group *cmd);

// ===== builtin/builtin_export.c =====
int			builtin_export(t_cmd_group *cmd, char ***env_ptr);

// ===== builtin/builtin_pwd.c =====
int			builtin_pwd(t_cmd_group *cmd);

// ===== builtin/builtin_unset.c =====
int			builtin_unset(t_cmd_group *cmd, char ***env_ptr);

// ===== builtin/builtin_utils.c =====
bool		is_valid_identifier(char *arg);
int			find_env_index(char **env, char *arg);
int			append_env(char ***env, char *arg);
int			set_env_var(char ***env, char *arg);
void		inner_unset(char *cur, char ***env_ptr);
bool		is_valid_echo_flag(char *arg);
bool		is_valid_numeric(char *str);
int			get_exit_stats(int exit_status);

// ===== builtin/builtin_env_utils.c =====
char		*get_env_value(char **env, const char *key);
void		sort_env(char **env);
void		print_formatted_env(char *entry, int fd);
void		print_env(char **env, int fd);

void		close_fd(int fd);
int			tab_len(char **tab);
char		*ft_getenv(char **env, const char *key);
char		**copy_tab(char **tab);
void		*ft_safe_calloc(size_t count, size_t size, char *msg);
int			ft_strcmp(const char *s1, const char *s2);
void		free_tab(char **tab);

// ===== signal/signals.c =====
void	signal_handler(t_sig_mode mode);
void    print_signal_exit(int status);

// ===== signal/signals_heredoc.c =====
void    heredoc_interrupt(int signum);
void    main_heredoc_interrupt(int signum);
#endif