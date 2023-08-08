/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:30:55 by marine            #+#    #+#             */
/*   Updated: 2023/08/08 14:54:27 by madavid          ###   ########.fr       */
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

typedef struct s_lexer
{
	int				i;
	t_lexer_type	type;
	char			*word;
	struct s_lexer	*previous;
	struct s_lexer	*next;
}			t_lexer;

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
char	**ft_split_space(char const *str);
t_lexer	*lexer(char *input, t_lexer **root);
t_lexer_type	check_type(char *word);
t_lexer	*ft_new_lexer_node(char *input, int index);
t_lexer	*ft_last_lexer_node(t_lexer *node);
void	ft_node_lexer_add_back(t_lexer **node, t_lexer *new);
void	ft_print_lexer(t_lexer	**node);
void	ft_lexer_del_one(t_lexer *node);
void	ft_lexer_clear(t_lexer **node);
//void 			check_quote(char *input);
char	*ft_split_lexer(char const *str, int *i);

/* Parser */

/* Catégorie 3 */
/* Catégorie n */

#endif