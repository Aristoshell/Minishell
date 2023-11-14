/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:38:35 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/14 17:20:21 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv ;
	if (argc != 1)
		return (ft_dprintf(STDERR_FILENO, D_ER_ARG), 1);
	// if (isatty(STDIN_FILENO) != 1)
	// 	return (1);
	data = NULL;
	data = ft_create_data(envp);
	if (!data)
		return (ft_dprintf(STDERR_FILENO, D_ER_MEM), 1);
	if (prompt(data) == MEMORY_ERR_NB)
		return (ft_clean_t_data(data), 1);
	return (0);
}
