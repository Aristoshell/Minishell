#ifndef MINISHELL_H
# define MINISHELL_H

//include 
# include "../libft/header/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

//defines
// a mettre en majuscule
# define DIS_ERR_ARG "Error : Please launch minishell with no additional argument\n"
# define DIS_ERR_ENV "Error : Please launch minishell with env\n"
# define DIS_ERR_SYNTAX_QUOTE "Error : unclosed quote\n" // a adapter en fonction de quel token
# define DIS_ERR_SYNTAX_TOKEN "Error : syntax error near unexpected token\n" // a adapter en fonction de quel token
# define FUNCTION_SUCCESS	0
# define EXIT				1
# define MEMORY_ERROR_NB	2
# define MEMORY_ERROR_PT	NULL
# define SYNTAX_QUOTE_ERROR	3
# define SYNTAX_TOKEN_ERROR	4
# define LINE_IS_EMPTY		5
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

/* Lexer */

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

// romann : type = struct avec une valeur et un type donc changer les noms
typedef struct s_token
{
	char			*string;
	t_token_type	type;
	bool			join_with_next;
	bool			expand;
	t_open_quote	quote;
	bool			empty_node;
	bool			redir_file;
}			t_token;

typedef struct s_info
{
	int		nb_tokens; // a delete
	int		current_token; // a delete
	t_list	*tokens;
}			t_info;

/* Fin lexer */


/* Parsing */

typedef enum e_builtin
{
	no,
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
	ambiguous,
	stdin_,
	stdout_,
}			t_filetype;

typedef struct s_files
{
  char			*filename;
  t_filetype	filetype;
  bool			open;
  bool			redirect;
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
	int			current_cmd; // a sup apres louis
	int			nb_command; // a sup apres louis
	t_cmd		**cmd; // a sup apres louis
	t_envlist	*envp; // a garder
	int			exec_val;
}			t_data;

//fonctions
//hihi
/* Create and Init */

t_data		*ft_create_data(char **envp);
void		ft_init_data(t_data *data);
t_info		*create_info(t_info *info);
void		ft_init_info(t_info *info);
void		ft_reinit_data(t_data *data);
void		ft_reinit_info(t_info *info);

/* news*/
void		ft_clean_info_bis(t_info **info);

/* ERROR */
int			ft_error(int err_code);

/* PROMPT */
int				prompt(t_data *data);

/* PARSING */
int			parsing(t_data *data, const char *input);

/* Check pre parsing*/
bool		check_syntax(const char *str);
char		ft_check_open_quote(const char *input);
bool		check_redir(const char *str);
bool		check_pipe(const char *str);
void		ft_pass_when_quote(const char *str, int *i);
bool		ft_check_syntax_with_tokens(t_list *token);
bool		ft_check_empty_line(const char	*str, int i);

/* LEXER */
int	ft_tokenise(const char *input, t_info *info);
char			*get_token_val(const char *str, int *i);
t_token_type	get_token_type(const char *token);
void			ft_display_lexer(t_info info);
int		ft_del_quotes(t_info *info);
int		ft_remove_quotes(t_list *list, char quote);
int		ft_split_quotes(t_list *list);
int		ft_insert_next_node(int i, t_list *list);


/* PARSEUR */
int		ft_interprete(t_info *info, t_data *data);
void	ft_count_cmd(t_list *list, t_data *data);
int		ft_init_tab_cmd(t_data *data);
int		ft_init_cmd(t_data *data, int i);
int		ft_fill_cmd(t_cmd *cmd, t_list *list, t_data *data);
int		ft_fill_cmd_redirs(t_cmd *cmd, t_data *data, t_list *list);
int		ft_fill_cmd_redirs_files(t_cmd *cmd, t_list *list);
int		ft_fill_cmd_count_args(t_list *list);
int		ft_fill_cmd_init_tab_args(int nb_args, t_cmd *cmd);
int		ft_fill_cmd_fill_tab_args(t_cmd *cmd, t_list *list, int nb_args);
void	ft_display_tab_cmd(t_data *data);
void	ft_print_redir_files(t_list *list_files);

/* ERRORS */
int				ft_error(int err_code);

/* BOOLS */
bool		ft_is_space(char c);
bool		ft_is_simple_quote(char c);
bool		ft_is_double_quote(char c);
char		ft_is_quote(char c);
bool		ft_is_pipe(char c);
bool		ft_is_operator(char c);
bool		ft_is_separator(char c);
bool		ft_is_cmd_separator(char c);
bool		ft_is_dollar(char c);

/* Expand */
int	 ft_detatch_expand(t_list *list, int i);
int		ft_expand(t_info *info, t_envlist *envp, t_data *data);
int		ft_expand_val(t_list *list, t_envlist *env, t_data *data);

/* Join */
int	ft_join_nodes(t_list *list);

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
void		ft_clean_string(char **str);
void		ft_clean_2d_array(void **array, void (*clean_data)(void *));
void		ft_clean_2d_array_struct(void ***array, void (*clean_data)(void *));
void		ft_clean_t_token(t_token **token);
void		ft_clean_t_info(t_info *info);
void		ft_clean_t_cmd(t_cmd *cmd);
void		ft_clean_t_data(t_data *data);
void		ft_lst_env_delone(t_envlist *lst);
void		ft_lst_env_clear(t_envlist **lst);

/* Built-in */
void		display_env(t_envlist *env);
int			unset(t_envlist **env, char *key);
int			export(t_envlist **env, char *line);
void		display_export(t_envlist *env);

#endif