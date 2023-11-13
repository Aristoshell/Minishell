/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:55:50 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/13 13:52:46 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	error_dup2(void)
{
	int	i;

	i = 0;
	(void) i;
	g_glb = 990;
	ft_dprintf(STDERR_FILENO, "!!!!ERROR DUP2!!!!");
}

void	error_pipe(t_data *data, t_pipe *pipes)
{
	int	i;

	i = 0;
	(void) i;
	g_glb = 990;
	if (data->current_cmd > 1)
		waitpid(-1, NULL, 0);
	close(data->stdin_save);
	close(data->stdout_save);
	close_pipes(data, pipes);
	ft_clean_t_data(data);
	free(pipes);
	ft_dprintf(STDERR_FILENO, "!!!!ERROR PIPE!!!!");
	exit(99);
}

void	error_fork(t_data *data, t_pipe *pipes)
{
	int	i;

	i = 0;
	(void) i;
	g_glb = 990;
	if (data->current_cmd > 1)
		waitpid(-1, NULL, 0);
	close(data->stdin_save);
	close(data->stdout_save);
	close_pipes(data, pipes);
	ft_clean_t_data(data);
	free(pipes);
	ft_dprintf(STDERR_FILENO, "!!!!ERROR FORK!!!!");
	exit(99);
}
