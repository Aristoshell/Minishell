/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 18:37:40 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_data(t_data *data)
{
	*(data->current_cmd) = 0; //checker si jai bien modif la valeur
	data->nb_command = 0;
	//ft_clean_2d_array(data->cmd, fonction clean t_cmd);
	//ft_clean_2d_array(data->envp, fonction clean t_envlist);
}
