/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:59:34 by marine            #+#    #+#             */
/*   Updated: 2023/09/21 18:10:00 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_cmd(t_info *info, t_data *data)
{
	int		i;

	data->nb_command = 1;
	i = 0;
	while (i < info->nb_tokens)
	{
		if (info->tokens[i]->type <= 2)
			data->nb_command++;
		i++;
	}
	printf("nb commandes : %d\n", data->nb_command++);
}

void	init_cmd(t_cmd	*cmd)
{
	cmd->pid = -1;
	cmd->cmd_args = NULL;
	cmd->cmd_type = no;
	cmd->path_cmd = NULL;
	cmd->input = stdin_;
	cmd->output = stdout_;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
}

// penser a initialiser les currents

// void	check_redirect_in(t_cmd	*cmd, t_tokens **tokens, int *curr_cmd, int *curr_word)
// {
// 	if (word[0])
// }

// void	fill_cmd(t_cmd	*cmd, t_tokens **tokens, int *curr_cmd, int *curr_word)
// {
// 	while (tokens[*curr_word]->type > type_pipe)
// 	{
// 		check_redirect_in(cmd, tokens, curr_cmd, curr_word);
// 	}	
// }

/*
Composition commande

boucle tant quon a fini le tableau

	boucle jusqua ce quon n'ai pas de pipe
	
	1) Checker si redirection d'intfile
		si pas premier bout + ce que celui davant est une pipe
			--> redirection in pipe
		sinon si j'ai <<
			--> redirection heredoc avec separator = tab[+1]
		sinon si j'ai <
			--> redirection fichier de tab[+1]
		sinon
			--> no redirect
		attention ! bien verifier quon a un tab[+1], sinon renvoyer erreur i guess ?
	
	2) le truc actuel est une commande
		- checker si tab[i] est un built in ou pas
		tant qu'on na pas > ou >> ou | (faire bool opearateur redirection)
			- mettre dans **cmd_args les mots de tab[current]
	3) checker redirection out
		si > ou >> ou |
			si > open le suivant en mode edition, puis tant quon na pas de pipe on avance
			si >> open le suivant en mode append, puis tant quon na pas de pipe on avance
			si | pipe, pipe

	quand est ce que je check les ./ ???
*/

int	parser(t_info	*info, t_data *data)
{
	int		i;
	
	i = 0;
	//info->current = 0;
	ft_count_cmd(info, data);
	//checker si 0 cmd
	data->cmd = malloc(sizeof(t_cmd) * data->nb_command);
	if (!data->cmd)
		return (MEMORY_ERROR_NB); // attention check retour de cette fonction avant (previously on retournais -1) + effacer ce qui a ete alloue avant
	while (i < data->nb_command)
	{
		data->cmd[i] = malloc(sizeof(t_cmd));
		if(!data->cmd[i])
			return (MEMORY_ERROR_NB); // attention check retour de cette fonction avant (previously on retournais -1) + effacer ce qui a ete alloue avant
		init_cmd(data->cmd[i]);
		//fill_cmd(data->cmd[i], info->tokens, data->current_cmd, info->current_word);
		i++;
	}
	(void) i;
	free(data);
	return (0);
}

/* 
on reçoit une struct info avec
	- nb de mots
	- tableau de partitions avec les mots
on veut : une struct data avec
	- nb de commandes
	- un tableau de commandes avec le nom de la commande, ses CFLAGS et arguments, entrée et sortie standard


exemple :

je reçois

ls -la > hihi ; cat hihi > bruh ; ls -la | wc -l


- Etape 1 : compter le nombre de cmd
	- tant qu'on n'a pas de separateur de commandes 
- Etape 2 : une fois qu'on a le nb de commande
	- on va malloc le tableau de commande
	- dans une boucle on va un a un
		- malloc la struct cmd
		- innit cette struct cmd
		- remplir cette struct cmd à partir de info
*/
