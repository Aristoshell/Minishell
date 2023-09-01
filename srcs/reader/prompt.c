/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/01 19:08:29 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_2d_array(char ***tab)
{
	int	i;

	i = 0;
	char **two_di_array;
	two_di_array = *tab;
	if (two_di_array)
	{
		while (two_di_array[i])
		{
			ft_bzero(two_di_array[i], ft_strlen(two_di_array[i]));
			free(two_di_array[i]);
			two_di_array[i] = NULL;
			i++;
		}
		free (two_di_array);
		*tab = NULL;
	}
}

void	prompt(void)
{
	char	*input;
	char	**words;

	words = NULL;
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
				words = ft_split_space(input);
				int i = 0;
				while(words[i])
				{
					printf("mot %d |%s|\n", i, words[i]);
					i++;	
				}
			}
		}
		free(input);
		if (words)
			ft_free_2d_array(&words);
	}
}
