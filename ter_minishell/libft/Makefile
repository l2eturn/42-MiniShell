#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slimvutt <slimvutt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 08:16:50 by slimvutt          #+#    #+#              #
#    Updated: 2025/08/29 22:59:15 by slimvutt         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

SRCS			=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
					ft_isdigit.c ft_isprint.c ft_itoa.c \
					ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
					ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_putstr_fd.c \
					ft_strcmp.c ft_strchr.c ft_strlcpy.c\
					ft_striteri.c ft_strjoin.c ft_strlcat.c \
					ft_strlen.c ft_strmapi.c ft_strncmp.c ft_split.c\
					ft_strnstr.c ft_strrchr.c ft_strdup.c ft_calloc.c\
					ft_substr.c ft_strtrim.c ft_tolower.c ft_toupper.c\
					get_next_line.c get_next_line_utils.c\

SRCSB			=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
					ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c
					
#ft_lstmap_bonus.c
OBJS = ${SRCS:.c=.o}
OBJSB = ${SRCSB:.c=.o}
NAME = libft.a
LIBC = ar rcs
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

all: ${NAME}

bonus: ${NAME} ${OBJSB}
	${LIBC} ${NAME} ${OBJSB}
clean:
	${RM} ${OBJS} ${OBJSB}

fclean: clean
	${RM} ${NAME} ${bonus} 

re: fclean all

.PHONY : all bonus clean fclean re

#SRCS			=	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
#					ft_isdigit.c ft_isprint.c ft_itoa.c \
#					ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
#					ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
#					ft_putnbr_fd.c ft_putstr_fd.c \
#					ft_strcmp.c ft_strchr.c\
#					ft_striteri.c ft_strjoin.c ft_strlcat.c \
#					ft_strlen.c ft_strmapi.c ft_strncmp.c ft_split.c\
#					ft_strnstr.c ft_strrchr.c ft_strdup.c ft_calloc.c\
#					ft_substr.c ft_strtrim.c ft_tolower.c ft_toupper.c

#BONUS			=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
#					ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

#OBJS			= $(SRCS:.c=.o)
#OBJS_BONUS		= $(BONUS:.c=.o)
#CC				= cc
#RM				= rm -f
#CFLAGS			= -Wall -Wextra -Werror
#NAME			= libft.a
#LIBC			= ar rcs

#.c.o:
#				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
#all:			$(NAME)

#$(NAME): 		$(OBJS)
#				${LIBC} $(NAME) $(OBJS)
#				@clear
#				@echo
#				@echo "                    ██▓        ██▓    ▄▄▄▄        █████▒   ▄▄▄█████▓"
#				@sleep 0.1
#				@echo "                   ▓██▒       ▓██▒   ▓█████▄    ▓██   ▒    ▓  ██▒ ▓▒"
#				@sleep 0.1
#				@echo "                   ▒██░       ▒██▒   ▒██▒ ▄██   ▒████ ░    ▒ ▓██░ ▒░"
#				@sleep 0.1
#				@echo "                   ▒██░       ░██░   ▒██░█▀     ░▓█▒  ░    ░ ▓██▓ ░ "
#				@sleep 0.1
#				@echo "                   ░██████▒   ░██░   ░▓█  ▀█▓   ░▒█░         ▒██▒ ░ "
#				@sleep 0.1
#				@echo "                   ░ ▒░▓  ░   ░▓     ░▒▓███▀▒    ▒ ░         ▒ ░░   "
#				@sleep 0.1
#				@echo "                   ░ ░ ▒  ░    ▒ ░   ▒░▒   ░     ░             ░    "
#				@sleep 0.1
#				@echo "                     ░ ░       ▒ ░    ░    ░     ░ ░         ░      "
#				@sleep 0.1
#				@echo "                       ░  ░    ░      ░                             "
#				@sleep 0.1
#				@echo "                                           ░                        "
#				@sleep 0.1
#				@echo "                 ___          _          _   _           _____ ___ ___   "
#				@sleep 0.1
#				@echo "                / __|___  ___| |_____ __| | | |__ _  _  |_   _| __| _ \\  "
#				@sleep 0.1
#				@echo "               | (__/ _ \\/ _ \\ / / -_) _\` | | '_ \\ || |   | | | _||   /_ "
#				@sleep 0.1
#				@echo "                \\___\\___/\\___/_\\_\\___\\__,_| |_.__/\\_, |   |_| |___|_|_(_)"
#				@sleep 0.1
#				@echo "                                                  |__/                    "
#				@sleep 0.1
#				@echo
#				@echo "Successfully compiled!"

#bonus:			$(NAME) $(OBJS_BONUS)
#				${LIBC} $(NAME) $(OBJS_BONUS)

#clean:
#				$(RM) $(OBJS) $(OBJS_BONUS)

#fclean:			clean
#				$(RM) $(NAME) $(bonus)
#				@echo
#				@echo "                               ⣿⣿⠁⣬⠻⣶⣤⣍⠛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⠿⢿⣿"
#				@sleep 0.1
#				@echo "                               ⣿⡏⢰⢸⣷⢹⣿⣿⣶⡎⠉⢉⣉⡉⠉⠉⣩⣴⣶⣶⣶⣶⣶⢖⡂⠈⣿"
#				@sleep 0.1
#				@echo "                               ⣿⡇⠄⠈⣿⣴⣿⣿⣿⠄⢰⣾⡏⠄⢠⣾⣿⣿⠿⣿⣿⣿⠁⢾⡇⠄⣿"
#				@sleep 0.1
#				@echo "                               ⣿⡇⢰⣴⣾⡿⠟⠿⣿⣶⣿⣿⣷⣶⣿⡟⠁⠄⠄⣶⣍⢿⣶⣧⡇⢠⣿"
#				@sleep 0.1
#				@echo "                               ⣿⣧⢸⡿⠁⠄⠄⢹⣆⢻⣟⡋⢉⣽⣿⣆⡧⢔⣚⣛⣛⣾⣿⣿⠄⣾⣿"
#				@sleep 0.1
#				@echo "                               ⣿⣿⢸⡇⠷⠤⣀⣭⡭⣾⣿⡿⠙⠻⠿⠿⢻⣿⣿⣿⣿⣿⣿⣧⠄⢿⣿"
#				@sleep 0.1
#				@echo "                               ⣿⠇⢸⣿⣿⣿⣿⣿⣿⡆⠄⠄⠄⠄⠄⠄⢸⣿⣿⣿⣿⣿⣿⣿⣷⡀⣿"
#				@sleep 0.1
#				@echo "                               ⣿⢀⣿⣿⣿⠿⠿⢿⣿⣿⣄⠄⠄⣀⣶⣿⢸⣿⣿⣿⣿⣿⣿⣿⣇⠘⣿"
#				@sleep 0.1
#				@echo "                               ⣿⡀⢰⣿⠃⣤⣶⣤⣌⡻⣿⣆⢾⣿⣿⡿⣸⣿⣿⣿⣿⣿⡿⠿⢟⣀⣻"
#				@sleep 0.1
#				@echo "                               ⣿⣇⣚⡹⣄⠸⣿⣿⣿⣷⡘⢿⣌⣛⣛⣵⣿⣿⣿⣿⣿⣿⣷⡄⠄⣈⣿"
#				@sleep 0.1
#				@echo "                               ⣿⣿⡿⢣⡿⠄⣿⣿⣿⣿⣧⠘⣿⣿⣿⣿⣿⣿⣿⣿⣍⠉⣤⣤⣾⣿⣿"
#				@sleep 0.1
#				@echo "                               ⣿⠟⣠⡟⠃⣜⣛⣛⣻⣯⣭⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣌⠻⢿⣿⣿"
#				@sleep 0.1
#				@echo
#				@echo "Successfully cleaned Libft."
#				@echo

#re:				fclean $(NAME)

#.PHONY:			all clean fclean re bonus
