/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:48:34 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 20:51:44 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	exit_clean_child(t_data *data, t_pipe *pipes, char **envp, int exit_val)
{
	close_files(data);
	close(data->stdin_save);
	close(data->stdout_save);
	close_pipes(data, pipes);
	ft_clean_t_data(data);
	free_envp(envp);
	free(pipes);
	exit (exit_val);
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

	envp = list_to_array(data->envp);
	cmd = data->cmd[data->current_cmd];
	pipes = handle_redirection(data, pipes);
	handle_signals_exec();
	if (g_glb == 999)
		exit_clean_child(data, pipes, envp, 1);
	if (data->cmd[data->current_cmd]->cmd_type != no)
	{
		exec_val = handle_builtins(data, pipes);
		exit_clean_child(data, pipes, envp, exec_val);
	}
	return (child_process2(data, pipes, cmd, envp));
}

t_pipe	*gen_child(t_data *data, t_pipe *pipes)
{
	pid_t	pid;

	handle_heredoc(data, pipes);
	if (data->nb_command > 1 && data->current_cmd >= 1)
		pipes = new_pipes(data, pipes, data->current_cmd);
	if (data->cmd[data->current_cmd]->cmd_type != no \
		&& data->cmd[data->current_cmd]->cmd_type != no_cmd \
		&& data->nb_command == 1)
	{
		pipes = handle_redirection(data, pipes);
		if (g_glb == 999)
			return (data->exec_val = 1, pipes);
		data->exec_val = handle_builtins(data, pipes);
		return (pipes);
	}
	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
		child_process(data, pipes);
	else
		data->cmd[data->current_cmd]->pid = pid;
	return (pipes);
}
