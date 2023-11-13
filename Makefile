SRCS_FILES	= 	minishell.c \
				manage_t_data.c \
				prompt.c \
				utils.c \
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
				parsing/interpretor/ft_fill_cmd_args.c \
				parsing/interpretor/ft_fill_cmd_redirs.c \
				parsing/interpretor/ft_fill_cmd_redirs2.c \
				parsing/interpretor/ft_init_cmd.c \
				parsing/interpretor/ft_interprete.c \
				parsing/interpretor/ft_check_builtins.c \
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
				exec/redir2.c \
				exec/usefull.c \
				exec/heredoc.c \
				exec/heredoc2.c \
				exec/signal_heredoc.c  \
				exec/child.c \
				exec/close2.c \
				exec/signal_exec.c  \
				exec/signal_prompt.c  \
				exec/get_cmd.c \
				exec/all_redir_possibilities.c\
				builtins/cd.c  \
				builtins/env.c  \
				builtins/export.c  \
				builtins/export_display_quicksort.c \
				builtins/export_display.c \
				builtins/unset.c  \
				builtins/exit.c \
				builtins/echo.c \
				builtins/pwd.c \
				builtins/ft_putstr_fd_checked.c

LIBFT_FILES = 	memory/ft_bzero.c \
				memory/ft_memcpy.c \
				memory/ft_memmove.c \
				memory/ft_memset.c \
				memory/ft_memchr.c \
				memory/ft_memcmp.c \
				memory/ft_calloc.c \
				bools/ft_isalpha.c \
				bools/ft_isascii.c \
				bools/ft_isdigit.c \
				bools/ft_isalnum.c \
				bools/ft_isprint.c \
				strings/ft_strlcpy.c \
				strings/ft_strlen.c \
				strings/ft_strlcat.c \
				strings/ft_strchr.c \
				strings/ft_strchr_int.c \
				strings/ft_strrchr.c \
				strings/ft_strncmp.c \
				strings/ft_strcmp.c \
				strings/ft_strnstr.c \
				strings/ft_strdup.c \
				strings/ft_substr.c \
				strings/ft_strjoin.c \
				strings/ft_strjoin_ms.c \
				strings/ft_strtrim.c \
				strings/ft_split.c \
				chars/ft_tolower.c \
				chars/ft_toupper.c \
				numbers/ft_atoi.c \
				numbers/ft_itoa.c \
				display/ft_putchar_fd.c \
				display/ft_putstr_fd.c \
				display/ft_putendl_fd.c \
				display/ft_putnbr_fd.c \
				strings/ft_strmapi.c \
				strings/ft_striteri.c \
				linkedlists/ft_lstnew.c\
				linkedlists/ft_lstadd_front.c \
				linkedlists/ft_lstsize.c \
				linkedlists/ft_lstlast.c \
				linkedlists/ft_lstadd_back.c \
				linkedlists/ft_lstdelone.c \
				linkedlists/ft_lstclear.c \
				linkedlists/ft_lstiter.c \
				linkedlists/ft_lstmap.c \
				gnl/ft_get_next_line.c \
				printf/ft_printf_fd.c \
				printf/ft_printf_utils_fd.c \
				dprintf/converter1.c \
				dprintf/ft_dprintf.c \
				dprintf/ft_itoa_hex.c \
				dprintf/str_management.c \
				dprintf/converter2.c \
				dprintf/ft_itoa_u.c

				
PREFIX	= srcs

SRCS = $(addprefix ${PREFIX}/, ${SRCS_FILES})
OBJS = $(SRCS:.c=.o)
HEADERS = header/minishell.h \
			header/minishell_louis.h

PREFIX_LIB = libft/srcs
LIBFT_SRCS = $(addprefix ${PREFIX_LIB}/, ${LIBFT_FILES})
LIB = -Llibft -lft -lreadline
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

${LIBFT_DIR}%.o: ${LIBFT_DIR}%.c
	${CC} ${CFLAGS} ${CDCFLAGS} ${INCLUDE} -c $< -o $@

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

${LIBFT}: ${LIBFT_OBJS}
	echo -n "${BOLD_WHITE}⏳ COMPILING LIBFT${NC}"
	${MAKE} -sC ${LIBFT_DIR}
	echo "${GREEN}Done 💅${NC}"

${NAME}: ${OBJS} ${HEADERS}
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

.PHONY: re fclean all seed
.SILENT: