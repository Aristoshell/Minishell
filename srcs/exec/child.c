/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:48:34 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/15 07:51:10 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	exit_child_builtin(t_data *data, t_pipe *pipes, int exit_val)
{
	close_pipes(data, pipes);
	ft_clean_t_data(data);
	free(pipes);
	signal(SIGPIPE, SIG_DFL);
	exit(exit_val);
}

void	exit_clean_child(t_data *data, t_pipe *pipes, char **envp, int exit_val)
{
	if (exit_val == 99)
		printf("!!!!ERROR MALLOC!!!!");
	close_pipes(data, pipes);
	ft_clean_t_data(data);
	free_envp(envp);
	free(pipes);
	exit(exit_val);
}

int	child_process2(t_data *data, t_pipe *pipes, t_cmd *cmd, char **envp)
{
	char	*path_temp;
	char	*exec;
	int		exec_val;

	path_temp = find_path(envp);
	if (path_temp)
	{
		cmd->path_cmd = ft_split(path_temp, ':');
		if (!cmd->path_cmd)
			exit_clean_child(data, pipes, envp, 99);
	}
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if (!exec || cmd->cmd_type == no_cmd || g_glb == 990)
	{
		if (data->exec_val != 130)
			exec_val = g_glb;
		else
			exec_val = 130;
		exit_clean_child(data, pipes, envp, exec_val);
	}
	execve(exec, cmd->cmd_args, envp);
	ft_dprintf(STDERR_FILENO, "EXECVE FAILED\n");
	return (exit_clean_child(data, pipes, envp, 99), 1);
}

int	child_process(t_data *data, t_pipe *pipes)
{
	t_cmd	*cmd;
	char	**envp;
	int		exec_val;

	envp = NULL;
	reset_signals();
	close(data->stdin_save);
	close(data->stdout_save);
	envp = list_to_array(data->envp);
	if (envp == NULL)
		return (close_files(data), exit_clean_child(data, pipes, envp, 99), 99);
	cmd = data->cmd[data->current_cmd];
	pipes = handle_redirection(data, pipes);
	close_files(data);
	if (g_glb == 999)
		exit_clean_child(data, pipes, envp, 1);
	if (data->cmd[data->current_cmd]->cmd_type != no)
	{
		free_envp(envp);
		signal(SIGPIPE, SIG_IGN);
		exec_val = handle_builtins(data, pipes);
		exit_child_builtin(data, pipes, exec_val);
	}
	return (child_process2(data, pipes, cmd, envp));
}

t_pipe	*gen_child(t_data *data, t_pipe *pipes)
{
	pid_t	pid;

	handle_heredoc(data, pipes);
	if (data->cmd[data->current_cmd]->fd_in == -2)
		return (ctrl_c_heredoc(data, pipes));
	if (data->nb_command > 1 && data->current_cmd >= 1)
		pipes = new_pipes(data, pipes, data->current_cmd);
	if (data->cmd[data->current_cmd]->cmd_type != no \
		&& data->cmd[data->current_cmd]->cmd_type != no_cmd \
		&& data->nb_command == 1)
	{
		pipes = handle_redirection(data, pipes);
		if (g_glb == 999)
			return (data->exec_val = 1, pipes);
		return (data->exec_val = handle_builtins(data, pipes), pipes);
	}
	handle_signals_exec();
	pid = fork();
	if (pid == -1)
		error_fork(data, pipes);
	if (pid == 0)
		child_process(data, pipes);
	else
		data->cmd[data->current_cmd]->pid = pid;
	return (pipes);
}
