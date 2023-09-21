/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:58:51 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 01:59:27 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*init_data(t_data *data, char **envp)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (MEMORY_ERROR_PT);
	data->cmd = NULL;
	data->current_cmd = NULL;
	data->nb_command = -1;
	data->envp = ft_get_envp(envp);
	if (!data->envp)
		return (MEMORY_ERROR_PT); // attention, la il faudra effacer data // pb differencier err malloc et pas denv
}
