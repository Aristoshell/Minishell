/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_louis.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:16:08 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/15 21:33:52 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define BT_EXIT_ARG "minishell: exit: %s: numeric argument required\n"
# define A "minishell: cd: %s: Not a directory\n"

extern int	g_glb;

typedef struct s_pipe
{
	int	tube[2][2];
}	t_pipe;

int		cross_array_list(t_data *data);
void	init_pipe(t_pipe *pipes);

t_pipe	*gen_child(t_data *data, t_pipe *pipes);

int		handle_heredoc(t_data *data, t_pipe *pipes);
int		total_ascii(char **cmd, int multiplier);
char	*seeded_word(long nbr, char *alnum);
int		heredoc(char *filemame, char *limiter);
void	clean_heredoc(t_data *data, t_pipe *pipes, char *limiter);
t_pipe	*ctrl_c_heredoc(t_data *data, t_pipe *pipes);
void	print_warning(const char *limiter);

t_pipe	*new_pipes(t_data *data, t_pipe *pipes, int i);

t_pipe	*handle_redirection(t_data *data, t_pipe *pipes);
t_pipe	*redir_fd_to_fd(t_data *data, t_cmd *cmd, t_pipe *pipes);
t_pipe	*redir_pipe_to_pipe(t_data *data, t_pipe *pipes);
t_pipe	*redir_pipe_to_fd(t_data *data, t_cmd *cmd, t_pipe *pipes);
t_pipe	*redir_fd_to_pipe(t_data *data, t_cmd *cmd, t_pipe *pipes);
t_redir	redir_file_from(t_files *f, t_cmd *cmd, t_redir r);
t_redir	redir_file_to(t_files *f, t_cmd *cmd, t_redir r);
t_redir	redir_append(t_files *f, t_cmd *cmd, t_redir r);
void	redir_ambigous_in(t_files *f, t_cmd *cmd, t_redir r);
void	redir_ambigous_out(t_files *f, t_cmd *cmd, t_redir r);
t_redir	redir_from_heredoc(t_files *f, t_cmd *cmd, t_redir r);
t_redir	redir_from_file(t_files *f, t_cmd *cmd, t_redir r);

int		handle_builtins(t_data *data, t_pipe *pipes);
int		bt_exit(t_data *data, int i, t_pipe *pipes);
int		bt_echo(t_data *data, int to_do);
int		bt_pwd(t_data *data);
int		bt_cd(t_data *data);
void	manage_errno(char *arg);

int		child_process(t_data *data, t_pipe *pipes);

char	**list_to_array(t_envlist *list);

char	*get_args(char **argv);
char	*get_cmd(char **paths, char *cmd);
char	*nopath(char *cmd);
char	*find_path(char **envp);
char	**gen_first_cmd(char **argv);
char	**gen_sec_cmd(char **argv);
char	**gen_third_cmd(char **argv, int argc);

int		strlen_list(t_cmd **cmd);

void	wait_childs(t_data *data);

int		set_redir(t_cmd *cmd, t_list *l);

void	free_list_args(t_cmd **cmd, t_pipe *pipes, int len_list);
void	close_fd(t_cmd **cmd, int len_list, int stdin_, int stdout_);
void	close_and_free(t_pipe *pipes, int stdin_save, \
int stdout_save, int status);

void	close_pipes(t_data *data, t_pipe *pipes);

int		strlen_list(t_cmd **cmd);

int		ft_isnumber(char *str);

void	error_management(t_cmd *cmd, char *str, int exit_val);
void	error_dup2(void);
void	error_malloc(void);
void	pipe_error(t_data *data, t_pipe *pipes);
void	error_dup(t_data *data, int status);
void	error_fork(t_data *data, t_pipe *pipes);
void	error_pipe(t_data *data, t_pipe *pipes);
int		ft_putstr_fd_checked(char *s, int fd);

void	handle_signals_heredoc(t_data *data);
void	handle_signals_prompt(t_data *data);
void	handle_signals_exec(void);
void	reset_signals(void);

void	free_envp(char **a);
void	close_files(t_data *data);
void	unlink_files(t_data *data);

int		ft_envlstsize(t_envlist *lst);
char	*join_lign_env(t_envlist *list);
#endif