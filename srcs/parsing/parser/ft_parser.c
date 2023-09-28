/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:59:34 by marine            #+#    #+#             */
/*   Updated: 2023/09/28 13:34:36 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/* Pas encore gere :

- redirections
- expand
- entre quotes

*/

void	init_cmd(t_cmd *cmd)
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

int	count_args(t_info info)
{
	int nb_agrs = 0;
	while (info.current_token <= info.nb_tokens || info.tokens[info.current_token]->type != type_pipe) //ie. dernier token ou pipe
	{
		nb_agrs++;
		info.current_token++;
	}
	return (nb_agrs);
}

int	create_cmd_args_tab(int nb_args, t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd->cmd_args)
		return (MEMORY_ERROR_NB);
	return (FUNCTION_SUCCESS);
}

int	create_cmd_arg(int nb_args, t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd->cmd_args)
		return (MEMORY_ERROR_NB);
	return (FUNCTION_SUCCESS);
}

int	fill_cmd(t_cmd *cmd, t_in_out out_prev, t_info *info)
{
	int	nb_args;

	//test pipe infile
	if (out_prev && out_prev == type_pipe)
		cmd->fd_in = type_pipe;
	nb_args = count_args(*info); //compter nb de args dans ma command
	if (create_cmd_args_tab(nb_args, cmd) == MEMORY_ERROR_NB) // creer le tableau d'args de la command
		return (MEMORY_ERROR_NB);
	// le remplir avec ce que jai dans chaque token.val
	int i = 0;
	while (i <= nb_args)
	{
		if (i == nb_args)
		{//create last qui va etre egal a NULL
			cmd->cmd_args[i] = malloc(sizeof(char) * 1);	
			if (!cmd->cmd_args[i])
				return (MEMORY_ERROR_NB); // GRRRRR
			cmd->cmd_args[i][0] = '\0';
		}
		else
		{//creer les autres
			cmd->cmd_args[i] = ft_strdup((const char*)info->tokens);
			if (!cmd->cmd_args[i])
				return (MEMORY_ERROR_NB); // GRRRRR
		}
		i++;
		info->current_token++;
	}
	// test pipe outfile
	if (info->tokens[info->current_token]->type == type_pipe)
		cmd->fd_out = type_pipe;
	return (FUNCTION_SUCCESS);
}


int	ft_parser(t_info	*info, t_data *data)
{
	int		i;
	
	i = 0;
	//info->current = 0;
	ft_count_cmd(*info, data);
	//checker si 0 cmd, normalement ce sera deja fait car 1) ligne vide renvoi juste le parseur, mais 2) attention avec envoi de just ""
	if (ft_init_tab_cmd(data) !=  FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	// remplir le tableau
	/*
		while (i < data->nb_command)
	{
		data->cmd[i] = malloc(sizeof(t_cmd));
		if(!data->cmd[i])
			return (MEMORY_ERROR_NB); // attention check retour de cette fonction avant (previously on retournais -1) + effacer ce qui a ete alloue avant
		init_cmd(data->cmd[i]);
		fill_cmd(data->cmd[i], data->cmd[i-1]->fd_out, info);
		i++;
	}
	(void) i;
	*/
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
