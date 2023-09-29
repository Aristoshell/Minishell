/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:56:33 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/29 15:10:09 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell_louis.h"


void	error_management(t_cmd *cmd, char *str, int exit_val)
{
	if (!cmd)
		return ;
	printf("%s\n",str);
	//set la value de retour a exit_val
	//free le plus de truc possible
	exit(exit_val);
}

void	error_dup2(void)
{
	printf("error dup2");
	exit(1);
}

void	error_pipe(void)
{
	printf("error pipe");
	exit(1);
}

void	error_fork(void)
{
	printf("error_fork");
	exit(1);
}

void	error_malloc(void)
{
	printf("error_malloc");
	exit(1);
}
