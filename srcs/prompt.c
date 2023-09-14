/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/14 19:46:44 by madavid          ###   ########.fr       */
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
				dprintf(2, "aristoshell : syntax error\n"); //penser a mettre une fonction dprintf recoded + adapter le message derreur
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

int	parse_envp(t_data *data, char **envp)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) envp;
	if (argc == 1)
	{
		prompt();
		return (0);
	}
	return (perror("Error : Please launch minishell with no additional argument"), -1);
}