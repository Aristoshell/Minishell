/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/26 14:39:12 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_exit(const char *input)
{
	if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)// a changer, car ca doit faire partie de lexec
	{
		// ft_dprintf(STDIN_FILENO, "exit\n"); mettre ailleurs
		// clear_history(); //peut etre qu'il faudra le mettre dans le return de prompt car je sais pas si ca va marcher la
		return (true);
	}
	return (false);
}

int	prompt(t_data *data)
{
	int			function_return;
	const char	*input;

	while (1)
	{
		input = readline(PROMPT_COLOUR"aristoshell$ "PROMPT_RESET);
		if (input && input[0] != 0)
		{
			if (check_exit(input)) // utilise seulement ici pour quitter proprement mais on nen naura plus besoin apres
			{
				free((void *)input);
				rl_clear_history();
				return (EXIT); //penser a bien tout free
			}
			add_history(input); //il faudra bien le free
			function_return = parsing(data, input);
			free((void *)input);
			if (function_return != FUNCTION_SUCCESS)
				ft_error(function_return);
			// if(execution(data) == EXIT)
			// 	return (EXIT);
			//ft_reinit_data(data);
		}
	}
	rl_clear_history();
	return(FUNCTION_SUCCESS);
}
