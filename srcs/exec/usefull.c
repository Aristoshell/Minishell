/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:59:05 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"


/*
retourne la taille du tableau de liste
*/

int	strlen_list(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (-1);
	while (cmd[i])
		i++;
	return (i);
}
