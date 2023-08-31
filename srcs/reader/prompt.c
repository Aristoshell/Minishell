/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/08/31 13:45:32 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*input;
	char	**words;
	while (1)
	{
		input = readline("\033[93maristoshell$ \033[0m");
		add_history(input);
		if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)
		{
			printf("exit\n");
			free(input);
			clear_history();
			return ;
		}
		if (input && input[0] != 0)
		{
			if (check_open_quote(input) != 0)
				dprintf(2, "aristoshell : syntax error near unclosed quote\n"); //penser a mettre une fonction dprintf recoded
			else
			{	
				words = ft_split(input, 32);
				int i = 0;
				while(words[i])
				{
					printf("mot %d |%s|\n", i, words[i]);
					i++;	
				}
			}
		}
		free(input);
		//free le double tableau
	}
}
