/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:55:50 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 16:56:10 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	error_dup2(void)
{
	printf("erno : %sn", strerror(errno));
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
