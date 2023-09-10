/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:59:34 by marine            #+#    #+#             */
/*   Updated: 2023/09/10 17:18:31 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_cmd(t_info *info, t_data *data)
{
	int		i;

	data->nb_command = 1;
	i = 0;
	while (i < info->nb_words)
	{
		if (info->words[i]->token <= 2)
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

// void	fill_cmd(t_cmd	*cmd, t_parts **words, int *current)
// {
// 	while (words[*current]->token >= word)
// 	{
// 		/* code */
// 	}	
// }

int	parser(t_info	*info)
{
	int		i;
	t_data	*data;
	
	i = 0;
	info->current = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	ft_count_cmd(info, data);
	//checker si 0 cmd
	data->cmd = malloc(sizeof(t_cmd) * data->nb_command);
	if (!data->cmd)
		return (-1); //supp autre chose ?
	while (i < data->nb_command)
	{
		data->cmd[i] = malloc(sizeof(t_cmd));
		if(!data->cmd[i])
			return (-1); //supp autre chose
		init_cmd(data->cmd[i]);
		//fill_cmd(data->cmd[i], info->words, info->current);
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
	- un tableau de commandes avec le nom de la commande, ses flags et arguments, entrée et sortie standard


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

