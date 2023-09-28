/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:59:34 by marine            #+#    #+#             */
/*   Updated: 2023/09/28 14:08:38 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


int	count_args(t_info *info)
{
	int nb_agrs = 0;
	while (info->current_token <= info->nb_tokens || info->tokens[info->current_token]->type != type_pipe) //ie. dernier token ou pipe
	{
		nb_agrs++;
		info->current_token++;
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

int	fill_cmd(t_cmd *cmd, t_in_out out_prev, t_info *info, bool first)
{
	int	nb_args;

	//test pipe infile
	ft_fill_cmd_test_infile(cmd, info, out_prev, first);
	
	nb_args = count_args(info); //compter nb de args dans ma command
	printf("nb args : %d\n", nb_args);
	/*
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
	*/
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
	// partie en train detre testee : remplir le tableau
	while (i < data->nb_command)
	{
		ft_init_cmd(data, i);
		if (i == 0)
			fill_cmd(data->cmd[i], data->cmd[i]->fd_out, info, true);//vraiment a changer car degueu
		else
			fill_cmd(data->cmd[i], data->cmd[i-1]->fd_out, info, false);
		i++;
	}
	//fin test
	return (0);
}
