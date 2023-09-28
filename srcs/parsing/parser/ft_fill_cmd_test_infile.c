/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_test_infile.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:03:38 by madavid           #+#    #+#             */
/*   Updated: 2023/09/28 14:06:16 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_cmd_test_infile(t_cmd *cmd, t_info *info, t_in_out out_prev, bool first)
{
	if (!first && out_prev == type_pipe) 
	{
		cmd->fd_in = type_pipe; // ca ca sera a change car si on a des redir, la pipe marche plus, ou alors, je laisserai Louis le changer
		info->current_token++;
	}
}