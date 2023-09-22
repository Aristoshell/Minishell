/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_t_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:36:44 by madavid           #+#    #+#             */
/*   Updated: 2023/09/22 18:45:02 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*peut etre quil faut un **data pour bien le clean ?*/

void	ft_clean_t_data(t_data *data)
{
	if (!data)
		return ;
	//ft_clean_string(data->input); //jenleve vu que ca fait bugger
	if (data->envp)
		ft_lst_env_clear(&data->envp);
	free(data);
	data = NULL;
}