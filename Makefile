# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madavid <madavid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 17:16:40 by marine            #+#    #+#              #
#    Updated: 2023/09/14 16:13:12 by madavid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	= 	prompt.c \
				reader/bools.c \
				reader/check_pipes.c \
				reader/check_quotes.c \
				reader/check_redir.c \
				lexer/ft_split_spaces.c \
				parser/parser.c

PREFIX	= srcs

SRCS = $(addprefix ${PREFIX}/, ${SRCS_FILES})

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft -lreadline

INCLUDE	= -Ilibft -Iheader -Ireadline

CC    = cc

FLAGS  = -Wall -Wextra -Werror -g3 #-fsanitize=address

NAME    = minishell

DEPS			=	${SRCS:.c=.d}

.c.o:
	${CC} ${FLAGS} ${CDFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	${MAKE} -C libft
	${CC} ${FLAGS} ${OBJS} ${LIB} -o ${NAME}

all: ${NAME}

clean:
	${MAKE} -C libft clean
	rm -f ${OBJS}
	rm -f ${DEPS}

fclean: clean
	${MAKE} -C libft fclean
	rm -f ${NAME}

re: fclean all

.PHONY: re fclean all
