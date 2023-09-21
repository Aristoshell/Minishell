/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_t_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:58:51 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 13:32:58 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->cmd = NULL;
	data->current_cmd = NULL;
	data->nb_command = -1;
	return (data);
}

t_data	*create_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (MEMORY_ERROR_PT);
	init_data(data)
	data->envp = ft_get_envp(envp);
	if (!data->envp)
		return (MEMORY_ERROR_PT); // attention, la il faudra effacer data // pb differencier err malloc et pas denv
	return (data);
}
