NAME 		:= Exec_Minishell

SRCS_FILES		:= set_up_cmd.c\
				main.c\
				temporary/from_marine.c\
				exec.c\
				close.c\
				error.c\
				free.c\
				redir.c\
				usefull.c\
				builtins/exit.c\
				builtins/echo.c\


SRCS_FILE = srcs/
HEADER := header/minishell.h

LIBFT := ./libft/libft.a
LIBFT_LIB := ./libft

CC := cc
CC_FLAGS := -Wall -Wextra -Werror
RM := rm -f

SRCS := $(addprefix $(SRCS_FILE), $(SRCS_FILES))
OBJS := ${SRCS:.c=.o}

%.o : %.c	${HEADER}
	    ${CC} ${CC_FLAGS} -g -c $< -o $@

${NAME}:	${LIBFT} ${OBJS} 
	 ${CC} ${CC_FLAGS} -o ${NAME} ${OBJS} ${LIBFT}

${LIBFT}:
		make -C ${LIBFT_LIB}

all:	${NAME}

clean:
	    ${RM} ${OBJS}
		make clean -C ${LIBFT_LIB}

seed :
	${RM} *.seed ${RM} */*.seed

fclean:	clean
		make seed
	    ${RM} ${NAME} ${LIBFT} 

re:	    fclean 
		make all

.PHONY: all clean fclean re