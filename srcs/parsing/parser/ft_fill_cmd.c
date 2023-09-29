/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 19:44:27 by madavid           #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd(t_cmd *cmd, t_in_out out_prev, t_info *info, bool first)
{
	int	nb_args;

	ft_fill_cmd_test_in(cmd, info, out_prev, first);
	nb_args = ft_fill_cmd_count_args(info);
	if (ft_fill_cmd_init_tab_args(nb_args, cmd) == MEMORY_ERROR_NB) // creer le tableau d'args de la command
		return (MEMORY_ERROR_NB);
	if (ft_fill_cmd_fill_tab_args(cmd, info, nb_args) != FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	ft_fill_cmd_test_out(cmd, info);
	return (FUNCTION_SUCCESS);
}
