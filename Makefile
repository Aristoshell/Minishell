# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marine <marine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 17:16:40 by marine            #+#    #+#              #
#    Updated: 2023/09/21 01:59:56 by marine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	= 	minishell.c \
				init/init_t_data.c \
				prompt.c \
				parsing/bools/ft_is_cmd_separator.c \
				parsing/bools/ft_is_operator.c \
				parsing/bools/ft_is_separator.c \
				parsing/bools/ft_is_quote.c \
				parsing/bools/ft_is_space.c \
				parsing/checks/ft_check_pipes.c \
				parsing/checks/ft_check_quotes.c \
				parsing/checks/ft_check_redir.c \
				parsing/checks/ft_check_syntax.c \
				parsing/envp/ft_get_val.c \
				parsing/envp/ft_new_envvar.c \
				parsing/envp/ft_get_envp.c \
				parsing/envp/ft_get_key.c \
				parsing/envp/ft_print_env.c \
				parsing/envp/ft_set_flag \
				parsing/lexer/ft_split_spaces.c \
				parsing/parser/parser.c \
				parsing/lists/ft_lst_env_add_back.c \
				parsing/lists/ft_lst_env_add_front.c \
				parsing/lists/ft_lst_env_last.c \
				parsing/lists/ft_lst_env_new.c \
				parsing/lists/ft_lst_env_pop.c \
				builtins/env.c \
				builtins/export.c \
				builtins/unset.c \
				clean/ft_clean_str \
				clean/ft_clean_structs.c \
				clean/ft_clean_2d_array \
				clean/ft_clean_string.c \
				clean/ft_clean_t_envlist.c \
				errors/errors.c

PREFIX	= srcs

SRCS = $(addprefix ${PREFIX}/, ${SRCS_FILES})

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft -lreadline
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE	= -Ilibft -Iheader -Ireadline

CC    = cc

CFLAGS  = -Wall -Wextra -Werror -g3 -fsanitize=address

NAME    = minishell

DEPS			=	${SRCS:.c=.d}


#################
#### DISPLAY ####
#################

RED=\033[0;31m
BOLD_WHITE=\033[1m
GREEN=\033[1;32m
ORANGE=\033[0;33m
YELLOW=\033[1;33m
BLUE=\033[1;36m
NC=\033[0m # No Color


#################
##### RULES #####
#################

all: ${LIBFT} ${NAME}

${LIBFT}:
	echo -n "${BOLD_WHITE}⏳ COMPILING LIBFT${NC}"
	${MAKE} -sC ${LIBFT_DIR}
	echo "${GREEN}Done 💅${NC}"

${NAME}: ${OBJS}
	echo -n "${BOLD_WHITE}⏳ COMPILING MINISHELL${NC}"
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}
	echo "${GREEN}Done 💅${NC}"

.c.o:
	${CC} ${CFLAGS} ${CDCFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}


clean:
	echo -n "${BOLD_WHITE}🧹 CLEANING OBJECTS\t${NC}"
	${MAKE} -sC ${LIBFT_DIR} clean
	${RM} ${OBJS}
	${RM} ${DEPS}
	echo "${GREEN}Done 💅${NC}"


fclean: clean
	echo -n "${BOLD_WHITE}🧹 CLEANING EXEC\t${NC}"
	${MAKE} -sC ${LIBFT_DIR} fclean
	${RM} ${NAME}
	echo "${GREEN}Done 💅${NC}"

re : fclean
	${MAKE}

.PHONY: re fclean all
.SILENT: