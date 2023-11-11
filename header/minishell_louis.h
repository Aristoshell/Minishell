#ifndef MINISHELL_LOUIS_H
# define MINISHELL_LOUIS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stddef.h>

extern int g_glb;


char	*get_args(char **argv);
char	*get_cmd(char **paths, char *cmd);
char	*nopath(char *cmd);
char	*find_path(char **envp);
char	**gen_first_cmd(char **argv);
char	**gen_sec_cmd(char **argv);
char	**gen_third_cmd(char **argv, int argc);

int		strlen_list(t_cmd **cmd);

int		cross_array_list(t_data *data);
t_pipe	*gen_child(t_data *data, t_pipe *pipes);
t_pipe	*new_pipes(t_pipe *pipes, int i);
void	wait_childs(t_data *data);
int		child_process(t_data *data, t_pipe *pipes);

t_pipe	*handle_redirection(t_data *data, t_pipe *pipes);
int		set_redir(t_cmd *cmd, t_list *l);
int		handle_builtins(t_data *data, t_pipe *pipes);

void	free_list_args(t_cmd **cmd, t_pipe *pipes, int len_list);
void	close_fd(t_cmd **cmd, int len_list, int stdin_, int stdout_);
void	close_and_free(t_pipe *pipes, int stdin_save, int stdout_save, int status);

void	close_pipes(t_data *data, t_pipe *pipes);

int		strlen_list(t_cmd **cmd);

int		ft_isnumber(char *str);
int		bt_exit(t_data *data, int i, t_pipe *pipes);

int		bt_echo(t_data *data, int to_do);
int		bt_pwd(t_data *data);
int		bt_cd(t_data *data);
// void	display_export(t_envlist *env);




/* Redirs */
void	redir_from(t_cmd *cmd, t_files *f, int *fail_open);
void	redir_to(t_cmd *cmd, t_files *f);
void	redir_append(t_cmd *cmd, t_files *f);
int		redir_ambigous_in(t_cmd *cmd, t_files *f);
int		redir_ambigous_out(t_cmd *cmd, t_files *f);
t_pipe	*redir_fd_to_fd(t_data *data, t_cmd *cmd, t_pipe *pipes);
t_pipe	*redir_pipe_to_pipe(t_data *data, t_pipe *pipes);
t_pipe	*redir_pipe_to_fd(t_data *data, t_cmd *cmd, t_pipe *pipes);
t_pipe	*redir_fd_to_pipe(t_data *data, t_cmd *cmd, t_pipe *pipes);


void	error_pipe(void);
void	error_dup2(void);
void	error_malloc(void);
void	error_fork(void);

void    handle_signals_heredoc(t_data *data);
void    handle_signals_prompt(t_data *data);
void	handle_signals_exec(void);
void    reset_signals(void);
void	sighandler(int signum);

int		handle_heredoc(t_data *data);
int		heredoc(char *filemame, char *limiter);
char	*seeded_word(long nbr, char *alnum);
int		total_ascii(char **cmd, int multiplier);

int		ft_envlstsize(t_envlist *lst);
void	free_envp(char **a);
char	**list_to_array(t_envlist *list);

void	close_files(t_data *data);
#endif