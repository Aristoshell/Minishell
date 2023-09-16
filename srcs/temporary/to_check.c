/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:07 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/16 14:07:31 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void error_dup2(void)
{
	printf("error dup2");
}

void error_pipe(void)
{
	printf("error pipe");
}

int strlen_list(t_cmd *cmd[4])
{
	int i;

	i = 0;
	while(cmd[i])
		i++;
	return (i);
}

// t_pipex	new_pipe(t_pipex stocker, int i)
// {
// 	if (i != 1)
// 	{
// 		close(stocker.tube[0][0]);
// 		close(stocker.tube[0][1]);
// 	}
// 	stocker.tube[0][0] = stocker.tube[1][0];
// 	stocker.tube[0][1] = stocker.tube[1][1];
// 	if (pipe(stocker.tube[1]) != 0)
// 	{
// 		parent_free(stocker);
// 		exit(0);
// 	}
// 	return (stocker);
// }

void	first_child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	if (dup2(pipes->tube[1][1], 1) == - 1
		|| dup2(cmd->fd_in, 0) == -1)
		error_dup2();
	close(pipes->tube[1][0]);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if(!cmd->cmd_args)
		return ;
	execve(exec, cmd->cmd_args, envp);
}

void	mid_child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	if (dup2(pipes->tube[0][0], 0) == - 1
		|| dup2(pipes->tube[1][1], 1) == -1)
		error_dup2();
	close (pipes->tube[0][1]);
	close (pipes->tube[1][0]);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if(!cmd->cmd_args)
		return ;
	execve(exec, cmd->cmd_args, envp);
}

void	last_child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	if (dup2(pipes->tube[0][0], 0) == - 1
		|| dup2(cmd->fd_out, 1) == -1)
		error_dup2();
	close(pipes->tube[0][1]);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if(!cmd->cmd_args)
		return ;
	execve(exec, cmd->cmd_args, envp);
}

t_pipe *new_pipes(t_pipe *pipes, int i)
{
	if (i != 1)
	{
		close(pipes->tube[0][0]);
		close(pipes->tube[0][1]);
	}
	pipes->tube[0][0] = pipes->tube[1][0];
	pipes->tube[0][1] = pipes->tube[1][1];
	if (pipe(pipes->tube[1]) !=0 )
		error_pipe();
	return (pipes);
}

t_pipe	*gen_first_child(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	pid_t pid;
	
	if (pipe(pipes->tube[1]) != 0)
		error_pipe();
	pid = fork();
	if (pid == 0)
		first_child_process(cmd, pipes, envp);
	cmd->pid = pid;
	return(pipes);
}

t_pipe	*gen_mid_child(t_cmd *cmd, t_pipe *pipes, char **envp, int i)
{
	pid_t	pid;
	
	new_pipes(pipes, i);
	pid = fork();
	if (pid == 0)
		mid_child_process(cmd, pipes, envp);
	cmd->pid = pid;
	return(pipes);
}

t_pipe	*gen_last_child(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	pid_t pid;
	
	new_pipes(pipes, 0);
	pid = fork();
	if (pid == 0)
		last_child_process(cmd, pipes, envp);
	cmd->pid = pid;
	return(pipes);
}

void wait_childs(t_cmd *cmd[4])
{
	int i;
	
	i = 0;
	while(cmd[i])
	{
		waitpid(cmd[i]->pid, 0, 0);
		i++;
	}
}

void	close_pipes(t_pipe *pipes)
{
	close(pipes->tube[0][0]);
	close(pipes->tube[0][1]);
	close(pipes->tube[1][0]);
	close(pipes->tube[1][1]);
}
void	cross_array_list(t_cmd *cmd[4], char **envp)
{
	int 	i;
	int 	len_list;
	t_pipe 	*pipe;

	if (!envp)
		return;
	i = 1;
	pipe = malloc(sizeof(t_pipe));
	len_list = strlen_list(cmd);
	pipe = gen_first_child(cmd[0], pipe, envp);
	while(i < len_list - 1)
	{
		pipe = gen_mid_child(cmd[i], pipe, envp, i);
		i++;
	}
	pipe = gen_last_child(cmd[i], pipe, envp);
	close_pipes(pipe);
	wait_childs(cmd);
	return;
}