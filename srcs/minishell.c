/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/19 14:35:31 by madavid          ###   ########.fr       */
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

void	prompt()
{
	char	*input;
 	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		ft_dprintf(STDERR_FILENO, "Problem with memory allocation\n");
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


int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	t_envlist *parsed_env;
	if (argc == 1)
	{
		//parsed_env = get_envp(envp);
		(void) parsed_env;
		prompt();
		//display_env(parsed_env);
		//ft_lst_env_clear(&parsed_env);// mettre autre part plus tard
		return (0);
	}
	return (perror("Error : Please launch minishell with no additional argument"), -1);
}