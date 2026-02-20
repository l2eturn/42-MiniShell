TARGET = minishell
CC = cc
#CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ../mandatory/libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I. -I$(LIBFT_DIR)

SRC = main_exit.c input_pharse.c builtin.c
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(TARGET)


$(LIBFT):
	make -C $(LIBFT_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
