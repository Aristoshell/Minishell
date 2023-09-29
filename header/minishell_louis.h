/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_louis.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:39:47 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/29 15:11:09 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
}t_builtin;

typedef enum e_in_out
{
	stdin_,
	stdout_,
	heredoc_,
	append_,
	pipe_,
	file_
}			t_in_out;

typedef struct s_pipe
{
	int tube[2][2];
}	t_pipe;

typedef struct s_cmd
{
    pid_t                pid;
    char                **cmd_args;
    t_builtin            cmd_type;
    char                **path_cmd;
    t_in_out            input;
    t_in_out            output;
    char                *heredoc_name;
    char                *heredoc_sep;
    int                    fd_in;
    int                    fd_out;
}      t_cmd;

char	*get_args(char **argv);
char	*get_cmd(char **paths, char *cmd);
char	*nopath(char *cmd);
char	*find_path(char **envp);
char	**gen_first_cmd(char **argv);
char	**gen_sec_cmd(char **argv);
char	**gen_third_cmd(char **argv, int argc);

int		strlen_list(t_cmd **cmd);

void	cross_array_list(t_cmd **cmd, char **envp);
t_pipe	*gen_child(t_cmd **cmd, t_pipe *pipes, char **envp, int i, int *status);
t_pipe	*new_pipes(t_pipe *pipes, int i);
void	wait_childs(t_cmd **cmd);
int		child_process(t_cmd **tab_cmd, t_pipe *pipes, char **envp, int i);

t_pipe	*handle_redirection(t_cmd *cmd, t_pipe *pipes);
void	handle_builtins(t_cmd **cmd, char **envp, int i);

void	free_list_args(t_cmd **cmd, t_pipe *pipes, int len_list);
void	close_list_args(t_cmd **cmd, int len_list);

void	close_pipes(t_pipe *pipes);

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
