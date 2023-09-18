/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usefull.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:59:05 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 10:32:14 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
retourne la taille du tableau de liste
*/

int strlen_list(t_cmd *cmd[4])
{
	int i;

	i = 0;
	while(cmd[i])
		i++;
	return (i);
}