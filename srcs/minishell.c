/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/20 22:12:33 by madavid          ###   ########.fr       */
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


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
// checker si env -i
	if (argc != 1)
		return (perror(ERR_ARG), 1);
	data = init_data(data, envp);
	if (!data)
		return (MEMORY_ERROR_NB); //checker ce que je dois effacer
	if (prompt(data) == MEMORY_ERROR_NB);
		return (MEMORY_ERROR_NB); //checker ce que je dois effacer
	return (0);
}