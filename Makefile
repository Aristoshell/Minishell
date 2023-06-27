# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marine <marine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 17:16:40 by marine            #+#    #+#              #
#    Updated: 2023/06/27 17:52:10 by marine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	= 	main.c \
				prompt.c

PREFIX	= srcs

SRCS = $(addprefix ${PREFIX}/, ${SRCS_FILES})

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft -lreadline

INCLUDE	= -Ilibft -Iheader -Ireadline

CC    = cc

FLAGS  = -Wall -Wextra -Werror #-g3 #-fsanitize=address

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
