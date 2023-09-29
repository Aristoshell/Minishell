/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_test_in.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:03:38 by madavid           #+#    #+#             */
/*   Updated: 2023/09/28 14:06:16 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_fill_cmd_test_out(t_cmd *cmd, t_info *info)
{
	if (info->current_token < info->nb_tokens && info->tokens[info->current_token]->type == type_pipe)
		cmd->output = pipe_;
}