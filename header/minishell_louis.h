#ifndef MINISHELL_LOUIS_H
# define MINISHELL_LOUIS_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<string.h>
# include<limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stddef.h>

extern int glb;

typedef struct s_pipe
{
	int tube[2][2];
}	t_pipe;

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
void	handle_builtins(t_data *data);

void	free_list_args(t_cmd **cmd, t_pipe *pipes, int len_list);
void	close_list_args(t_cmd **cmd, int len_list, int stdin_, int stdout_);

void	close_pipes(t_data *data, t_pipe *pipes);

int		strlen_list(t_cmd **cmd);

int		ft_isnumber(char *str);
void	bt_exit(t_cmd **cmd, int i);

int		bt_echo(t_cmd **cmd_tab, int to_do);
int		bt_pwd(void);

void	error_management(t_cmd *cmd, char *str, int exit_val);
void	error_pipe(void);
void	error_dup2(void);
void	error_malloc(void);
void	error_fork(void);

void    handle_signals_heredoc();
int		heredoc(char *limiter, t_data *data);
#endif