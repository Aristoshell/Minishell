/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:39:19 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/16 14:46:43 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	manage_errno(char *arg)
{
	if (errno == 2)
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n", arg);
	if (errno == 13)
		ft_dprintf(2, "minishell: cd: %s: Permission denied\n", arg);
}

void	init_pipe(t_pipe *pipes)
{
	pipes->tube[0][0] = -1;
	pipes->tube[0][1] = -1;
	pipes->tube[1][1] = -1;
	pipes->tube[1][1] = -1;
}

void	error_dup(t_data *data, int status)
{
	if (status == 1)
		close (data->stdin_save);
	ft_clean_t_data(data);
	ft_dprintf(2, "!!!!ERROR DUP!!!!\n");
	exit(99);
}

void	ft_free_2d_array(char **two_di_array)
{
	int	i;

	i = 0;
	if (two_di_array)
	{
		while (two_di_array[i])
		{
			free(two_di_array[i]);
			two_di_array[i] = NULL;
			i++;
		}
		free(two_di_array);
	}
}
