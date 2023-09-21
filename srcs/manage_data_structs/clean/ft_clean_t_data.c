/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/21 14:44:31 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*peut etre quil faut un **data pour bien le clean ?*/

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	*(data->current_cmd) = 0; //checker si jai bien modif la valeur
	data->nb_command = 0;
	if (data->input)
		free (data->input);
	//ft_clean_2d_array(data->cmd, fonction clean t_cmd);
	//ft_clean_2d_array(data->envp, fonction clean t_envlist);
	// il faut aussi free data non ??? et le mettre a null 
}
