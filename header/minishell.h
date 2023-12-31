/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:55:39 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 03:54:08 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//include 
# include "../libft/header/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>

//defines
// a mettre en majuscule
# define D_ER_MEM  "Problem with memory allocation\n"
# define D_ER_ARG "minishell: please launch minishell with no argument\n"
# define D_ER_SYN_QUOTE "minishell: unclosed quote\n"
# define D_ER_SYN_PIPE "minishell: syntax error near unexpected token `|'\n"
# define D_ER_SYN_NL "minishell: syntax error near unexpected token `newline'\n"
# define D_ER_SYN_FROM "minishell: syntax error near unexpected token `<'\n"
# define D_ER_SYN_HERED "minishell: syntax error near unexpected token `<<'\n"
# define D_ER_SYN_TO "minishell: syntax error near unexpected token `>'\n"
# define D_ER_SYN_APPEND "minishell: syntax error near unexpected token `>>'\n"
# define D_ER_CMD_NF "minishell: %s: command not found\n"
# define D_ER_PERM "minishell: %s: Permission denied\n"
# define D_ER_AMB "minishell: %s: ambiguous redirect\n"
# define D_ER_NO_FILDIR "minishell: %s: No such file or directory\n"
# define D_ER_ISDIR "minishell: %s: Is a directory\n"
# define D_ER_EXPAND "minishell: export: `%s': not a valid identifier\n"
# define D_ER_EXPORT_UNSET "minishell: %s: %c%c: invalid option\n"
# define D_ER_ENV "env: '%s': please use env with no option or argument\n"
# define FUNCTION_SUCCESS	0
# define STOP				2
# define EXIT				1
# define MEMORY_ERR_NB		99
# define MEMORY_ERROR_PT	NULL
# define PERM_DENIED_ERROR	7
# define NO_FILEDIR_ERROR	8
# define WRONG_CMD_ARG		16
# define ERROR_BUILTIN		17
# define DOUBLE_QUOTE 		34
# define SIMPLE_QUOTE 		39
# define MASK_SET			0x10
# define MASK_EXPORT		0x01
# define MASK_ENV			0x11
# define RED				"\033[1;31m"
# define GREEN				"\033[1;32m"
# define ORANGE				"\033[1;33m"
# define YELLOW				"\033[1;33m"
# define PROMPT_COLOUR		"\001\033[1;33m\002"
# define PROMPT_RESET		"\001\033[0m\002"
# define BLUE				"\033[1;36m"
# define NC					"\033[0m"

//typedefs

typedef int	t_flag;

typedef enum e_open_quote
{
	no_q,
	true_q,
	simple_q,
	double_q
}			t_open_quote;

typedef enum e_token_type
{
	type_default,
	type_pipe,
	type_word,
	type_from,
	type_to,
	type_heredoc,
	type_append
}			t_token_type;

typedef struct s_token
{
	char			*string;
	t_token_type	type;
	bool			join_with_next;
	bool			expand;
	t_open_quote	quote;
	bool			redir_file;
}			t_token;

typedef enum e_builtin
{
	no,
	no_cmd,
	cmd_echo,
	cmd_cd,
	cmd_pwd,
	cmd_export,
	cmd_export_print,
	cmd_unset,
	cmd_env,
	cmd_exit,
}			t_builtin;

typedef enum e_filetype
{
	pipe_in_,
	pipe_out_,
	file_from,
	file_to,
	heredoc_,
	append_,
	ambiguous_in,
	ambiguous_out,
	stdin_,
	stdout_,
}			t_filetype;

typedef struct s_redir
{
	int		fail_open;
	bool	prev_in;
	bool	prev_out;
}				t_redir;

typedef struct s_files
{
	char			*filename;
	t_filetype		filetype;
	bool			open;
	bool			redirect;
	int				fd;
}				t_files;

typedef struct s_cmd
{
	pid_t				pid;
	char				**cmd_args;
	t_builtin			cmd_type;
	char				**path_cmd;
	t_list				*list_files;
	int					fd_in;
	int					fd_out;
	t_filetype			input;
	t_filetype			output;
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
	int				current_cmd;
	int				nb_command;
	t_cmd			**cmd;
	t_envlist		*envp;
	t_list			*tokens;
	int				exec_val;
	int				stdin_save;
	int				stdout_save;
	int				dollar_loc;
	t_token			*curr_token;
}			t_data;

t_data			*ft_create_data(char **envp);
void			ft_init_data(t_data *data);
void			ft_reinit_data(t_data *data);
void			ft_clean_t_data(t_data *data);

char			*ft_get_val(char *line);
t_envlist		*ft_new_envvar(char *line);
int				ft_get_envp(t_envlist **env, char **envp);
char			*ft_get_key(char *line, int sep);
void			ft_print_env(t_envlist *env);
void			ft_set_flag(int *flag, char *val);
void			ft_lst_env_add_back(t_envlist **lst, t_envlist *new);
void			ft_lst_env_add_front(t_envlist **lst, t_envlist *new);
t_envlist		*ft_lst_env_last(t_envlist *lst);
t_envlist		*ft_lst_env_new(const char *key, char *val);
void			unset_single(t_envlist **lst, char *key);
void			ft_lst_env_delone(t_envlist *lst);
void			ft_lst_env_clear(t_envlist **lst);

int				prompt(t_data *data);
void			ft_free_2d_array(char **two_di_array);

void			ft_display_lexer(t_data data);
int				parsing(t_data *data, const char *input);
char			ft_check_open_quote(const char *input);
bool			ft_check_open_quote_bool(const char *input);
bool			ft_check_syntax_with_tokens(t_list *token);
bool			ft_check_empty_line(const char	*str, int i);
int				ft_tokenise(const char *input, t_data *data);
char			*get_token_val(const char *str, int *i);
t_token_type	get_token_type(const char *token);
void			ft_clean_token(t_token *token);
int				ft_insert_next_node(int i, t_list *list);

int				ft_del_quotes(t_data *data);
int				ft_remove_quotes(t_list *list, char quote);
int				ft_split_quotes(t_list *list);
int				ft_detach_quotes(int i, t_list *list, char quote);

int				ft_detatch_expand(t_list *list, int i);
int				ft_expand(t_envlist *envp, t_data *data);
int				ft_expand_val(t_list *list, t_envlist *env, t_data *data);
int				ft_join_nodes(t_list *list, t_data *data);

int				ft_interprete(t_data *data);
void			ft_count_cmd(t_list *list, t_data *data);
int				ft_init_tab_cmd(t_data *data);
int				ft_init_cmd(t_data *data, int i);
int				ft_fill_cmd(t_cmd *cmd, t_list *list, t_data *data);
int				ft_fill_cmd_redirs(t_cmd *cmd, t_data *data, t_list *list);
int				ft_fill_cmd_redirs_files(t_cmd *cmd, t_list *list);
void			ft_clean_t_file(t_files *file);
int				ft_fill_cmd_count_args(t_list *list);
int				ft_fill_cmd_init_tab_args(int nb_args, t_cmd *cmd);
int				ft_fill_cmd_fill_tab_args(t_cmd *cmd, t_list *list, int n_args);
int				ft_check_builtin(t_cmd *cmd);

bool			ft_is_space(char c);
bool			ft_is_simple_quote(char c);
bool			ft_is_double_quote(char c);
char			ft_is_quote(char c);
bool			ft_is_pipe(char c);
bool			ft_is_operator(char c);
bool			ft_is_separator(char c);
bool			ft_is_cmd_separator(char c);
bool			ft_is_dollar(char c);

int				display_env(t_envlist *env, char **args);
int				unset(t_envlist **env, char **key);
int				export(t_envlist **env, char **tab);
int				display_export(t_envlist *env, char **args);
void			ft_quick_sort(char ***tab, int low, int high);

#endif