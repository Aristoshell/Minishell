/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:30:55 by marine            #+#    #+#             */
/*   Updated: 2023/07/05 16:04:42 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//include 
# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>

//defines

//typedefs

/* Lexer */

typedef enum e_lexer_type
{
	word,
	token_pipe,
	token_in,
	token_out
}			t_lexer_type;

typedef struct s_lexer
{
	int				index;
	t_lexer_type	type;
	char			*word;
	struct 	s_lexer	*previous;
	struct 	s_lexer	*next;
}			t_lexer;

/* Parsing */


typedef enum e_builtin
{
	echo_,
	echo_n_,
	cd_,
	pwd_,
	export_,
	unset_,
	env_,
	exit_,
	no
}			t_builtin;

typedef enum e_in_out
{
	stdin_,
	stdout_,
	pipe_,
	file_
}			t_in_out;


typedef struct s_cmd
{
	char				**command;
	t_builtin			command_source;
	char				*path_cmd;
	t_in_out			input;
	int					fd_in;
	t_in_out			output;
	int					fd_out;
	struct s_cmd		*next;
}			t_cmd;

typedef struct s_data
{
	int		pipe;
	t_cmd	*first_arg;
}			t_data;


//fonctions

/* Général */
void	prompt(void);

/* Lexer */
// void check_quote(char *input);
char			**ft_split_space(char const *str);
t_lexer			*lexer(char *input, t_lexer **root);
t_lexer_type	check_type(char *word);
t_lexer			*ft_new_lexer_node(char *input, int index);
t_lexer			*ft_last_lexer_node(t_lexer *node);
void			ft_node_lexer_add_back(t_lexer **node, t_lexer *new);
void 			ft_print_lexer(t_lexer	*node);
void			ft_lexer_del_one(t_lexer *node);
void			ft_lexer_clear(t_lexer **node);

/* Catégorie 2 */
/* Catégorie 3 */
/* Catégorie n */

#endif