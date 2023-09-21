/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 20:37:41 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv ;
	if (argc != 1)
		return (perror(ERR_ARG), 1);
	if (!envp)
		return (perror(ERR_ENV), 1);
	data = NULL;
	data = create_data(data, envp);
	if (!data)
		return (MEMORY_ERROR_NB); //checker ce que je dois effacer
	if (prompt(data) == MEMORY_ERROR_NB)
		return (MEMORY_ERROR_NB); //add ce que je dois effacer
	//fonction pour tout clean
	return (0);
}
