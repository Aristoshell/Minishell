/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/08 15:14:47 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_info(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_words)
	{		
 		ft_bzero(info->words[i]->string, ft_strlen(info->words[i]->string));
		if (info->words[i]->string)
			free(info->words[i]->string);
		info->words[i]->string = NULL;
		i++;
	}
	if (info->nb_words > 0)
		free(info->words);
	info->nb_words = -1;
}

void	prompt(void)
{
	char	*input;
 	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		dprintf(2, "Problem with memory allocation\n");
	info->words = NULL;
	while (1)
	{
		input = readline("\033[93maristoshell$ \033[0m");
		add_history(input);
		if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)
		{
			printf("exit\n");
			free(input);
			free(info);
			clear_history();
			return ;
		}
		if (input && input[0] != 0)
		{
			if (check_open_quote(input) != 0)
				dprintf(2, "aristoshell : syntax error near unclosed quote\n"); //penser a mettre une fonction dprintf recoded
			else
			{	
				ft_split_space(input, info);
				int i = 0;
				while(i < info->nb_words)
				{
					printf("[%d] [%d]: %s\n", i, info->words[i]->token, info->words[i]->string);
					i++;	
				}
				parser(info);
			}
		}
		free(input);
		if (info->words)
			ft_free_info(info);
	}
}
