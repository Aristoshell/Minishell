/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 14:53:40 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_exit(char *input, t_info	*info)
{
	if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)// a changer, car ca doit faire partie de lexec
	{
		ft_dprintf(STDIN_FILENO, "exit\n");
		free(input);
		input = NULL;
		free(info); //plutot utiliser clean info que jai code. 
		info = NULL;
		clear_history(); //peut etre qu'il faudra le mettre dans le return de prompt car je sais pas si ca va marcher la
		return (true);
	}
	return (false);
}

int	prompt(t_data *data)
{
 	t_info	*info;
	int		function_return;

	info = create_info(info);
	if (!info)
		return (error(MEMORY_ERROR_NB)); //besoin d'effacer qq chose aussi
	while (1)
	{
		data->input = readline(YELLOW"aristoshell$ "NC);
		if (data->input && data->input[0] != 0)
		{
			if (check_exit(data->input, info)); // utilise seulement ici pour quitter proprement mais on nen naura plus besoin apres
				return (EXIT); //penser a bien tout free
			add_history(data->input);
			function_return = parsing(data, info);
			if (function_return != FUNCTION_SUCCESS);
				ft_error(function_return, data, info);
			if(exec(data) == EXIT)
				return (EXIT);
		}
	}
}
