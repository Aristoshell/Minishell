/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/23 01:00:53 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_exit(char *input, t_info *info)
{
	if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)// a changer, car ca doit faire partie de lexec
	{
		ft_dprintf(STDIN_FILENO, "exit\n");
		free(input);
		input = NULL;
		if (info)
			ft_clean_t_info(info);
		clear_history(); //peut etre qu'il faudra le mettre dans le return de prompt car je sais pas si ca va marcher la
		return (true);
	}
	return (false);
}

int	prompt(t_data *data)
{
 	t_info	*info;
	int		function_return;
	char	*input;

	info = NULL;
	info = create_info(info);
	if (!info)
		return (ft_error(MEMORY_ERROR_NB, data, info)); //besoin d'effacer qq chose aussi
	while (1)
	{
		input = readline(YELLOW"aristoshell$ "NC);
		if (input && input[0] != 0)
		{
			if (check_exit(input, info)) // utilise seulement ici pour quitter proprement mais on nen naura plus besoin apres
				return (EXIT); //penser a bien tout free
			add_history(input); //il faudra bien le free
			function_return = parsing(data, info, input);
			free(input);
			if (function_return != FUNCTION_SUCCESS)
				ft_error(function_return, data, info);
			// if(execution(data) == EXIT)
			// 	return (EXIT);
			//ft_reinit_data(data);
		}
	}
}
