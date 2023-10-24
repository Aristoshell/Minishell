SRCS_FILES	= 	minishell.c \
				manage_t_data.c \
				prompt.c \
				utils.c \
				errors/ft_errors.c \
				parsing/bools/ft_check_empty_line.c \
				parsing/bools/ft_is_cmd_separator.c \
				parsing/bools/ft_is_dollar.c \
				parsing/bools/ft_is_operator.c \
				parsing/bools/ft_is_pipe.c \
				parsing/bools/ft_is_quote.c \
				parsing/bools/ft_is_separator.c \
				parsing/bools/ft_is_space.c \
				parsing/checks_syntax/ft_check_quotes.c \
				parsing/checks_syntax/ft_check_syntax_with_tokens.c \
				parsing/delete_quotes/ft_del_quotes_detach.c \
				parsing/delete_quotes/ft_del_quotes_remove_quotes.c \
				parsing/delete_quotes/ft_del_quotes.c \
				parsing/envp/lists/ft_lst_env_add_back.c \
				parsing/envp/lists/ft_lst_env_add_front.c \
				parsing/envp/lists/ft_lst_env_last.c \
				parsing/envp/lists/ft_lst_env_new.c \
				parsing/envp/lists/ft_lst_env_pop.c \
				parsing/envp/ft_get_envp.c \
				parsing/envp/ft_get_key.c \
				parsing/envp/ft_get_val.c \
				parsing/envp/ft_new_envvar.c \
				parsing/envp/ft_print_env.c \
				parsing/envp/ft_set_flag.c \
				parsing/envp/lists/ft_lst_env_delone.c \
				parsing/envp/lists/ft_lst_env_clear.c \
				parsing/expand/ft_expand_detach.c \
				parsing/expand/ft_expand_join_nodes.c \
				parsing/expand/ft_expand_val.c \
				parsing/expand/ft_expand.c \
				parsing/interpretor/ft_display_cmd.c \
				parsing/interpretor/ft_fill_cmd_args.c \
				parsing/interpretor/ft_fill_cmd_redirs.c \
				parsing/interpretor/ft_init_cmd.c \
				parsing/interpretor/ft_interprete.c \
				parsing/tokeniser/ft_display_tokens.c \
				parsing/tokeniser/ft_tokenise_get_token_info.c \
				parsing/tokeniser/ft_tokenise.c \
				parsing/parsing.c \
				exec/set_up_cmd.c \
				exec/exec.c \
				exec/close.c \
				exec/error.c \
				exec/free.c \
				exec/redir.c \
				exec/usefull.c \
				exec/heredoc.c \
				exec/signals.c  \
				builtins/cd.c  \
				builtins/env.c  \
				builtins/export.c  \
				builtins/export_display_quicksort.c \
				builtins/export_display.c \
				builtins/unset.c  \
				builtins/exit.c \
				builtins/echo.c \
				builtins/pwd.c
				
PREFIX	= srcs

SRCS = $(addprefix ${PREFIX}/, ${SRCS_FILES})

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft -lreadline
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE	= -Ilibft -Iheader -Ireadline

CC    = cc

CFLAGS  = -Wall -Wextra -Werror -g3

NAME    = minishell

DEPS			=	${SRCS:.c=.d}

ifeq ($(debug), true)
	CFLAGS += -fsanitize=address,undefined
endif

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
	${RM} *.seed ${RM} */*.seed
	echo "${GREEN}Done 💅${NC}"


fclean: clean
	echo -n "${BOLD_WHITE}🧹 CLEANING EXEC\t${NC}"
	${MAKE} -sC ${LIBFT_DIR} fclean
	${RM} ${NAME}
	echo "${GREEN}Done 💅${NC}"

re : fclean
	${MAKE}

seed :
	${RM} *.seed ${RM} */*.seed

.PHONY: re fclean all seed
.SILENT: