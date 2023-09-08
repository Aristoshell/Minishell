/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:30:55 by marine            #+#    #+#             */
/*   Updated: 2023/09/08 11:01:22 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//include 
# include "../libft/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

//defines
# define double_quote 34
# define simple_quote 39
 
//typedefs

/* Lexer */


typedef enum e_open_quote
{
	no_q,
	simple_q,
	double_q
}			t_open_quote;

typedef enum e_lexer_type
{
	word,
	token_pipe,
	token_in,
	token_out
}			t_lexer_type;

typedef struct s_parts
{
	char			*string;
	t_lexer_type	token;
}			t_parts;

typedef struct s_lexer
{
	int				i;
	t_lexer_type	type;
	char			*word;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}			t_lexer;

typedef struct s_info
{
	int	nb_words;
	t_parts	**words;
}			t_info;


/* Parsing */

typedef enum e_builtin
{
	cmd_echo,
	cmd_echo_n,
	cmd_cd,
	cmd_pwd,
	cmd_export,
	cmd_unset,
	cmd_env,
	cmd_exit,
	no
}			t_builtin;

typedef enum e_in_out
{
	stdin_,
	stdout_,
	heredoc_,
	append_,
	pipe_,
	file_
}			t_in_out;

typedef struct s_cmd
{
	pid_t				pid;
	char				**cmd_args;
	t_builtin			cmd_type;
	char				**path_cmd;
	t_in_out			input;
	t_in_out			output;
	int					fd_in;
	int					fd_out;
	struct s_cmd		*next;
}			t_cmd;

typedef struct s_indexer
{
	char	*word;
	int		index;
}			t_indexer;

typedef struct s_data
{
	int				pipe;
	t_open_quote	open_quote;
	t_cmd			*first_arg;
}			t_data;

//fonctions

/* Général */
void	prompt(void);
char 	*manage_quote(char *input);
char 	check_open_quote(char *input);
char 	*close_quote(char quote);

/* Lexer */
int	ft_split_space(char const *str, t_info *info);

/* Parser */

/* Catégorie 3 */
/* Catégorie n */

#endif