/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:39:47 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 08:33:52 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<string.h>
# include<readline/readline.h>
# include<readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stddef.h>
# include "../libft/libft.h"

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


void	child_process(t_cmd *cmd, t_pipe *pipes, char **envp);
char	*get_args(char **argv);
char	*get_cmd(char **paths, char *cmd);
char	*nopath(char *cmd);
char	*find_path(char **envp);
char	**gen_first_cmd(char **argv);
char	**gen_sec_cmd(char **argv);
char	**gen_third_cmd(char **argv, int argc);
void	cross_array_list(t_cmd *cmd[4], char **envp);