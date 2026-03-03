TARGET  = minishell
TEST    = test_builtin
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g3

LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

INCLUDES  = -I. -I$(LIBFT_DIR)

SRC =   main.c \
		utils.c \
        utils2.c \
        utils3.c \
        main_exit.c \
        tokenizer.c \
        tokenizer_utils.c \
        quotes_check.c \
		signal/signals.c \
        signal/signals2.c \
		signal/signals_heredoc.c \
        builtin/builtin_dispatch.c \
        builtin/builtin_cd.c \
        builtin/builtin_echo.c \
        builtin/builtin_env.c \
        builtin/builtin_env_utils.c \
        builtin/builtin_exit.c \
        builtin/builtin_export.c \
        builtin/builtin_pwd.c \
        builtin/builtin_unset.c \
        builtin/builtin_utils.c \
        builtin/builtin_utils2.c \
        builtin/builtin_time.c \
        builtin/builtin_time_utils.c \
        expander/expander.c \
        expander/expander_token.c \
        expander/expander_var.c \
        executor/exec_iofiles_utils.c \
        executor/exec_cmd.c \
        executor/exec_cmd2.c \
        executor/exec_cmd3.c \
        executor/exec_cmd4.c \
        executor/exec_cmd_utils.c \
        executor/exec_heredoc.c \
        executor/exec_heredoc2.c \
        executor/exec_iofiles.c \
        executor/exec_iofiles_check.c \
        debug.c \
        utils_tab.c \
        parser/parser_cmd.c \
        parser/parser_check.c \
        parser/parser_check2.c \
        parser/parser_check_utils.c \
        parser/parser_get_info.c \
        parser/parser_infiles.c \
        parser/parser_outfiles.c \
        cleanup.c \
        cleanup_2.c \
        parser/parser_cmd_help.c

OBJ      = $(SRC:.c=.o)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(LIBFT) $(TARGET)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(TARGET) $(TEST)
	rm -f a.out $(LIBFT_DIR)/libft.h.gch

re: fclean all

.PHONY: all clean fclean re test