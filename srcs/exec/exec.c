/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:52:16 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/13 12:13:39 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	g_glb = 0;

int	wait_child(t_data *data, t_cmd *cmd, int error_print)
{
	int	status;

	status = 0;
	if (cmd->pid != -1)
		waitpid(cmd->pid, &status, 0);
	if (data->nb_command > 1 || cmd->cmd_type == no)
		data->exec_val = WEXITSTATUS(status);
	if (WTERMSIG(status) == 2 && error_print == 0)
	{
		error_print = 1;
		printf("\n");
		data->exec_val = 130;
	}
	if (WTERMSIG(status) == 3 && error_print == 0)
	{
		error_print = 1;
		printf("Quit (core dumped)\n");
		data->exec_val = 131;
	}
	return (error_print);
}

void	wait_childs(t_data *data)
{
	int	i;
	int	status;
	int	error_print;

	error_print = 0;
	status = 0;
	(void) status;
	i = 0;
	while (i < data->nb_command)
	{
		error_print = wait_child(data, data->cmd[i], error_print);
		i++;
	}
}

t_pipe	*new_pipes(t_data *data, t_pipe *pipes, int i)
{
	if (data)
	{
		if (i > 1)
		{
			close(pipes->tube[0][0]);
			close(pipes->tube[0][1]);
		}
		pipes->tube[0][0] = pipes->tube[1][0];
		pipes->tube[0][1] = pipes->tube[1][1];
		if (pipe(pipes->tube[1]) != 0)
			error_pipe(data, pipes);
		return (pipes);
	}
	return (pipes);
}

t_pipe	*init_exec(t_data *data, t_pipe *pipes)
{
	data->stdin_save = dup(0);
	if (data->stdin_save == -1)
		error_dup(data, 0);
	data->stdout_save = dup(1);
	if (data->stdin_save == -1)
		error_dup(data, 0);
	data->current_cmd = 0;
	if (data->nb_command > 1)
	{
		pipes = malloc(sizeof(t_pipe));
		if (!pipes)
		{
			ft_dprintf(STDERR_FILENO, D_ER_MEM);
			pipe_error(data, pipes);
		}
		init_pipe(pipes);
		if (pipe(pipes->tube[1]) != 0)
		{
			ft_dprintf(STDERR_FILENO, "PIPE FUNCTION FAILED\n");
			free(pipes);
			pipe_error(data, pipes);
		}
	}
	return (pipes);
}

int	cross_array_list(t_data *data)
{
	t_pipe	*pipes;

	pipes = NULL;
	pipes = init_exec(data, pipes);
	while (data->current_cmd < data->nb_command)
	{
		pipes = gen_child(data, pipes);
		if (pipes == NULL && data->nb_command > 1)
			return (0);
		data->current_cmd++;
	}
	close_pipes(data, pipes);
	wait_childs(data);
	if (g_glb == 130)
		data->exec_val = 130;
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_files(data);
	free(pipes);
	unlink_files(data);
	return (0);
}
