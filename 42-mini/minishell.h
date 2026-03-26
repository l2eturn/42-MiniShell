/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2026/03/26 18:42:21 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <time.h>
# include <sys/resource.h>

# ifndef HOSTNAME
#  define HOSTNAME "host"
# endif

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

# define _POSIX_C_SOURCE 200809L
# define MAX_PROCESS 101
# define MAX_PIPE    100

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

typedef enum s_operator
{
	NONE,
	PIPE,
}	t_operator;

typedef struct s_infiles
{
	char					*filename;
	bool					is_heredoc;
	char					*lim;
	struct s_infiles		*next;
}	t_infiles;

typedef struct s_outfiles
{
	char					*filename;
	bool					is_append;
	struct s_outfiles		*next;
}	t_outfiles;

typedef struct s_cmd_group
{
	char					*cmds_str;
	char					**cmd_tokens;
	char					**in_filenames;
	char					**out_filenames;
	char					*cmd;
	char					**argv;
	char					***env_ptr;
	t_operator				operator;
	int						in_fd;
	int						out_fd;
	bool					is_heredoc;
	int						h_pipe[2];
	char					*lim;
	t_infiles				*in_files;
	t_outfiles				*out_files;
	bool					is_error;
	int						exit_status;
	struct s_cmd_group		*next;
	struct s_cmd_group		*prev;
}	t_cmd_group;

void		exit_msg(char *msg);
void		exit_cmd(char *cmd, char *err_msg, int exit_status);
void		exit_errno(int exit_status);

void		close_builtin_fds(t_cmd_group *cmd);
int			is_builtin(char *cmd);
int			execute_builtin(t_cmd_group *cmd);
int			execute_builtin_main(t_cmd_group *cmd);

int			builtin_cd(t_cmd_group *cmd);
int			update_pwd(char ***env_ptr);
int			update_oldpwd(char ***env_ptr, const char *saved_pwd);
int			builtin_echo(t_cmd_group *cmd);
int			builtin_env(t_cmd_group *cmd);
int			builtin_exit(t_cmd_group *cmd);
int			builtin_export(t_cmd_group *cmd, char ***env_ptr);
int			builtin_pwd(t_cmd_group *cmd);
int			builtin_unset(t_cmd_group *cmd, char ***env_ptr);
int			exit_with_arg(t_cmd_group *cmd);
void		builtin_exit_help(t_cmd_group *cmd);
bool		is_in_pipe(t_cmd_group *cmd);
void		do_exit(t_cmd_group *cmd, int exit_code);

bool		is_valid_identifier(char *arg);
int			find_env_index(char **env, char *arg);
int			append_env(char ***env, char *arg);
int			set_env_var(char ***env, char *arg);
void		inner_unset(char *cur, char ***env_ptr);
bool		is_valid_echo_flag(char *arg);
bool		is_valid_numeric(char *str);
int			get_exit_stats(int exit_status);

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
int			is_whitespace(char c);
int			is_quotation_mark(char c);
int			is_special_char(char c);

void		signal_handler(t_sig_mode mode);
void		signal_handler_heredoc(t_sig_mode mode);
void		print_signal_exit(int status);
void		heredoc_interrupt(int signum);
void		main_heredoc_interrupt(int signum);

char		**tokenizer(char *str);

void		expand_tokens(char **tokens, char ***env_ptr, int *exit_status);
void		strip_quotes(char **tokens);
char		*expand_token(char *token, char ***env_ptr, int *exit_status);
char		*expand_variable(char *token, int *i, char ***env_ptr,
				t_exp_tmp params);
int			is_expandable_char(char c);
char		*ft_strjoin_char1(char *str, char c);

char		**append_tab(char **tab, char *str);
char		**split_tokens(char **tokens);

t_cmd_group	*init_cmd_group(char *line, char ***env_ptr, int *exit_status);
bool		is_heredoc_token(char *token);
bool		is_append_token(char *token);
bool		is_simple_redirect(char *token, char c);
bool		is_pipe_token(char *token);
bool		is_valid_tokens(char *line);
bool		is_valid_tokens_np(char *line);
bool		is_redirect(char *str);
bool		is_valid_pipes(char **tokens, int i);
bool		is_valid_redirect(char **tokens, int i);
void		put_err_parese_redirect(char *tokens);
int			next_after_redirect(char **tab, int index);
char		**get_in_filenames(char **tab);
char		**get_out_filenames(char **tab);
char		*get_cmd(char **tab);
char		**get_argv(char **tab);
void		set_in_files(t_cmd_group *node);
void		set_out_files(t_cmd_group *node);

t_infiles	*new_infile(char *filename, bool is_h, char *lim);
t_outfiles	*new_outfile(char *filename, bool is_append);
void		print_cmd_group(t_cmd_group *g);

int			execute_command(t_cmd_group *cmd_lines);
int			cmd_len(t_cmd_group *cmd_lines);
char		*find_cmd(char *cmd, char **env);
int			open_pipes(int pipes[MAX_PIPE][2], int process_num);
void		close_pipes(int pipes[MAX_PIPE][2], int process_num);
void		close_all_fd(t_cmd_group *cmd_lines);
void		close_all(int pipes[MAX_PIPE][2], int process_num,
				t_cmd_group *cmd_lines);
void		dup_process(int index, int pipes[MAX_PIPE][2],
				t_cmd_group *cur, int process_num);
int			wait_pid_process(int pid[MAX_PROCESS], int process_num,
				t_cmd_group *cmd_lines);
int			inner_wait_process(int pid[MAX_PROCESS], int process_num,
				t_cmd_group *cmd_lines, int closed_process);
void		exec(int index, int pipes[MAX_PIPE][2],
				t_cmd_group *cmd_lines, int process_num);
int			loop_open(t_cmd_group *cmd_lines);
int			loop_in(t_cmd_group *cur);
int			loop_out(t_cmd_group *cur);
t_cmd_group	*get_cmd_at(t_cmd_group *cmd_lines, int index);
void		exec_cmd_not_found(t_cmd_group *cur);
int			run_single_builtin(t_cmd_group *cmd_lines);
void		ft_memmove_argv(char **argv);
int			heredoc(t_cmd_group *cur);
void		read_til_lim(t_cmd_group *cur);
void		heredoc_eof(t_cmd_group *cur);
void		loop_heredoc(t_cmd_group *cmd_lines);
int			check_in_access(char *filename, t_cmd_group *cur);
int			check_out_access(char *filename, t_cmd_group *cur);
void		fd_error_once(char *filename, t_cmd_group *cur, char *msg);
void		close_old(t_cmd_group *cur);

bool		is_completed_quotes(char *line);
int			is_token(char *str);
int			is_fully_quoted(char *src, int len);
char		*clean_token(char *token);

void		free_cmd_group(t_cmd_group *cmd_group);
void		free_env(char **env);
void		cleanup_shell(t_cmd_group *cmd_group, char **env);
void		cleanup_error(t_cmd_group *cmd_group);
void		free_tokens_only(char **tokens);
void		free_segments(char **segments);
void		exit_status_help_process_line(int *exit_status);
void		init_cmd_node_help(t_cmd_group *node, char ***env_ptr);
void		set_shlvl(char ***env_ptr);
int			handle_time_keyword(char *line, char ***env_ptr, int *exit_status);
int			handle_redirection(t_cmd_group *cur);
bool		first_redirect_is_out(t_cmd_group *cur);
void		print_diff(struct timeval s, struct timeval e, char *label);
void		print_time_val(long sec, long usec, char *label);
void		normalize_tv(long *sec, long *usec);
#endif
