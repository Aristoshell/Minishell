/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:30:55 by marine            #+#    #+#             */
/*   Updated: 2023/09/17 15:21:07 by madavid          ###   ########.fr       */
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
// a mettre en majuscule
# define DOUBLE_QUOTE 	34
# define SIMPLE_QUOTE 	39
# define MASK_SET		0x10
# define MASK_EXPORT	0x01
# define MASK_ENV		0x11
# define YELLOW "\033[93m"
# define NC		"\033[0m"


//typedefs

typedef int	t_flag;

/* Env */
typedef struct s_envlist
{
	char				*key;
	char				*val;
	int					flag;
	struct s_envlist	*next;
}					t_envlist;

/* Lexer */

typedef enum e_open_quote
{
	no_q,
	simple_q,
	double_q
}			t_open_quote;

typedef enum e_lexer_type
{
	token_pipe,
	token_word,
	token_in,
	token_out,
	token_heredoc,
	token_append
}			t_lexer_type;

// romann : token = struct avec une valeur et un type donc changer les noms
typedef struct s_parts
{
	char			*string;
	t_lexer_type	token;
}			t_parts;

typedef struct s_info
{
	int	nb_words;
	int	*current_word;
	t_parts	**words;
}			t_info;

/* Fin lexer */


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
	char				*heredoc_name;
	char				*heredoc_sep;
	int					fd_in;
	int					fd_out;
}			t_cmd;

typedef struct s_data
{
	int			*current_cmd;
	int			nb_command;
	t_cmd		**cmd;
	t_envlist	*envp;
}			t_data;

//fonctions

/* GENERAL */
void	prompt(void);
char 	*manage_quote(char *input);
char 	check_open_quote(char *input);
char 	*close_quote(char quote);

/* LEXER */
int	ft_split_space(char const *str, t_info *info);


/* PARSEUR */
int	parser(t_info	*info);

/* BOOLS */
bool	is_space(char c);
char	is_quote(char c);
bool	is_op(char c);
bool	is_separator(char c);
bool	is_cmd_separator(char c);

/* Check pre parsing*/
bool	check_syntax(char	*str);
void	pass_when_quote(char *str, int *i);
int		check_pipe(char *str);

/* Env n */
t_envlist	*ft_lst_env_new(char *key, char *val);
void	ft_lst_env_add_back(t_envlist **lst, t_envlist *new);
void	ft_lst_env_add_front(t_envlist **lst, t_envlist *new);
void	ft_lst_env_clear(t_envlist **lst);
t_envlist	*get_envp(char **envp);

#endif