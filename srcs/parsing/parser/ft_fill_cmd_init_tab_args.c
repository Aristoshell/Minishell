/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_init_tab_args.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:35:05 by madavid           #+#    #+#             */
/*   Updated: 2023/09/28 16:43:46 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_cmd_init_tab_args(int nb_args, t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd->cmd_args)
		return (MEMORY_ERROR_NB);
	return (FUNCTION_SUCCESS);
}
