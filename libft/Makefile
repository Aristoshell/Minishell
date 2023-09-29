# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: madavid <madavid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 21:49:59 by madavid           #+#    #+#              #
#    Updated: 2023/09/22 17:11:24 by madavid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

SRCS_FILES = 	memory/ft_bzero.c \
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

all: $(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS) 

clean :
	${RM} $(OBJS)
	
fclean : clean
	${RM} $(NAME)

re : fclean
	${MAKE}

.PHONY : all clean fclean re
#.SILENT: