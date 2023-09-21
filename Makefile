# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madavid <madavid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/01 17:16:40 by marine            #+#    #+#              #
#    Updated: 2023/09/21 20:36:51 by madavid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES	= 	minishell.c \
				prompt.c \
				builtins/cd.c \
				builtins/echo.c \
				builtins/env.c \
				builtins/export.c \
				builtins/unset.c \
				builtins/pwd.c \
				errors/ft_errors.c \
				manage_data_structs/clean/ft_clean_2d_array.c \
				manage_data_structs/clean/ft_clean_string.c \
				manage_data_structs/clean/ft_clean_t_data.c \
				manage_data_structs/clean/ft_clean_t_envlist.c \
				manage_data_structs/clean/ft_clean_t_envlist_node.c \
				manage_data_structs/clean/ft_clean_t_info.c \
				manage_data_structs/clean/ft_clean_t_parts.c \
				manage_data_structs/set/set_t_data.c \
				manage_data_structs/set/set_t_info.c \
				parsing/bools/ft_is_cmd_separator.c \
				parsing/bools/ft_is_operator.c \
				parsing/bools/ft_is_pipe.c \
				parsing/bools/ft_is_quote.c \
				parsing/bools/ft_is_separator.c \
				parsing/bools/ft_is_space.c \
				parsing/checks/ft_check_pipes.c \
				parsing/checks/ft_check_quotes.c \
				parsing/checks/ft_check_syntax.c \
				parsing/checks/ft_check_redir.c \
				parsing/envp/ft_get_envp.c \
				parsing/envp/ft_get_val.c \
				parsing/envp/ft_new_envvar.c \
				parsing/envp/ft_get_key.c \
				parsing/envp/ft_print_env.c \
				parsing/envp/ft_set_flag.c \
				parsing/lexer/ft_display_lexer.c \
				parsing/lexer/ft_lexer_count_tokens.c \
				parsing/lexer/ft_lexer_get_token_type.c \
				parsing/lexer/ft_lexer_get_token_val.c \
				parsing/lexer/ft_lexer.c \
				parsing/lists/ft_lst_env_add_back.c \
				parsing/lists/ft_lst_env_add_front.c \
				parsing/lists/ft_lst_env_last.c \
				parsing/lists/ft_lst_env_new.c \
				parsing/lists/ft_lst_env_pop.c \
				parsing/parsing.c
				
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