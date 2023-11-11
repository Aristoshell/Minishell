/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:52:16 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 16:52:41 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	g_glb = 0;

void	wait_childs(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_command)
	{
		if (data->cmd[i]->pid != -1)
			waitpid(data->cmd[i]->pid, &status, 0);
		if (data->nb_command > 1 || data->cmd[i]->cmd_type == no)
			data->exec_val = WEXITSTATUS(status);
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
			exit(789);
		return (pipes);
	}
	return (pipes);
}

void	init_pipe(t_pipe *pipes)
{
		pipes->tube[0][0] = -1;
		pipes->tube[0][1] = -1;
		pipes->tube[1][1] = -1;
		pipes->tube[1][1] = -1;
}

t_pipe	*init_exec(t_data *data, t_pipe *pipes)
{
	data->stdin_save = dup(0);
	data->stdout_save = dup(1);
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
	return (0);
}
