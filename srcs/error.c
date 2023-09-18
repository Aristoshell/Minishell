/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:56:33 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 11:26:20 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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
