/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 02:08:21 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prompt(t_data *data)
{
	char	*input;
 	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (error(MEMORY_ERROR_NB)); //besoin d'effacer qq chose aussi
	info->words = NULL;
	while (1)
	{
		// faire un wrapper, add input to history qui va check si l'input est pas vide pour pas add un !ligne a mon historique
		input = readline(YELLOW"aristoshell$ "NC);
		add_history(input);
		if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)// a changer, car ca doit faire partie de lexec
		{
			printf("exit\n");
			free(input);
			free(info);
			clear_history();
			return ;
		}
		if (input && input[0] != 0)
		{
			if (!check_syntax(input))
			{
				ft_dprintf(STDERR_FILENO, "aristoshell : syntax error\n"); //penser a mettre une fonction dprintf recoded + adapter le message derreur
				free(input);
				// penser a free les structures
				return ;
			}
			else
			{	
				ft_split_space(input, info);
				int i = 0;
				while(i < info->nb_words)
				{
					printf("[%d] [%d]: %s\n", i, info->words[i]->token, info->words[i]->string);
					i++;
				}
				parser(info); // ca va remplir la data
			}
		}
		free(input);
		// if (exec(t_data data) == exit)
			// exit
		if (info->words)
			ft_free_info(info); // a integre dans le parser
		// if (data.cmd) , free la cmd, mais cest louis qui va le faire
	}
}
