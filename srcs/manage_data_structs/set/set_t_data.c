/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_t_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:58:51 by marine            #+#    #+#             */
/*   Updated: 2023/09/22 18:56:09 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data(t_data *data)
{
	data->current_cmd = 0;
	data->nb_command = 0;
}

void	ft_reinit_data(t_data *data)
{
	ft_init_data(data);
	if (data->cmd)
		ft_clean_2d_array((void **)data->cmd, (void *)ft_clean_t_cmd);
}

t_data	*ft_create_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (MEMORY_ERROR_PT);
	ft_init_data(data);
	data->envp = ft_get_envp(envp);
	if (!data->envp)
		return (MEMORY_ERROR_PT); // attention, la il faudra effacer data // pb differencier err malloc et pas denv
	return (data);
}
