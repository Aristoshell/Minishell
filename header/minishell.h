/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:30:55 by marine            #+#    #+#             */
/*   Updated: 2023/09/20 20:46:58 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//include 
# include "../libft/header/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

//defines
// a mettre en majuscule
# define ERR_ARG 			"Error : Please launch minishell with no additional argument"
# define FUNCTION_SUCCES	0
# define MEMORY_ERROR_NB	1
# define MEMORY_ERROR_PT	NULL
# define DOUBLE_QUOTE 		34
# define SIMPLE_QUOTE 		39
# define MASK_SET			0x10
# define MASK_EXPORT		0x01
# define MASK_ENV			0x11
# define RED				"\033[1;31m"
# define GREEN				"\033[1;32m"
# define ORANGE				"\033[1;33m"
# define YELLOW				"\033[1;33m"
# define BLUE				"\033[1;36m"
# define NC					"\033[0m"

//typedefs

typedef int	t_flag;


/* Lexer */

typedef enum e_open_quote
{
	no_q,
	simple_q,
	double_q
}			t_open_quote;

typedef enum e_lexer_type
{
	token_default,
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
	no,
	cmd_echo,
	cmd_echo_n,
	cmd_cd,
	cmd_pwd,
	cmd_export,
	cmd_unset,
	cmd_env,
	cmd_exit,
}			t_builtin;

typedef enum e_in_out
{
	none,
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

typedef struct s_envlist
{
	const char			*key;
	char				*val;
	int					flag;
	struct s_envlist	*next;
}					t_envlist;

typedef struct s_data
{
	int			*current_cmd; // a sup apres louis
	int			nb_command; // a sup apres louis
	t_cmd		**cmd; // a sup apres louis
	t_envlist	*envp; // a garder
}			t_data;

 //fonctions

/* GENERAL */
void	prompt(void);
char 	*manage_quote(char *input);
char 	check_open_quote(char *input);
char 	*close_quote(char quote);

/* LEXER */
int		ft_split_space(char const *str, t_info *info);

/* PROMPT */
void	prompt();

/* PARSEUR */
int	parser(t_info	*info);

/* ERRORS */
int	error(int err_code);

/* BOOLS */
bool		ft_is_space(char c);
char		ft_is_quote(char c);
bool		ft_is_pipe(char c);
bool		ft_is_operator(char c);
bool		ft_is_separator(char c);
bool		ft_is_cmd_separator(char c);

/* Check pre parsing*/
bool		check_syntax(char	*str);
char		check_open_quote(char *input);
bool		check_redir(char *str);
bool		check_pipe(char *str);

/* Envp  */
char		*ft_get_val(char *line);
t_envlist	*ft_new_envvar(char *line);
t_envlist	*ft_get_envp(char **envp);
char		*ft_get_key(char *line, int sep);
void		ft_print_env(t_envlist *env);
void		ft_set_flag(int *flag, char *val);

/* Lists  */
void		ft_lst_env_add_back(t_envlist **lst, t_envlist *new);
void		ft_lst_env_add_front(t_envlist **lst, t_envlist *new);
t_envlist	*ft_lst_env_last(t_envlist *lst);
t_envlist	*ft_lst_env_new(const char *key, char *val);
void		ft_lst_env_pop(t_envlist **lst, char *key);

/* Clean*/
void		ft_clean_2d_array(void **array, void (*clean_data)(void *));
void		ft_clean_string(char *str);
void		ft_clean_t_parts(t_parts *part);

/* Built-in */
void		display_env(t_envlist *env);
int			unset(t_envlist **env, char *key);
int			export(t_envlist **env, char *line);
void		display_export(t_envlist *env);

#endif