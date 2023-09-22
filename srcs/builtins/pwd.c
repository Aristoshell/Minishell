/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 23:33:01 by marine            #+#    #+#             */
/*   Updated: 2023/09/22 17:09:03 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	pwd(void)
{
	char	*working_dir;

	working_dir = NULL;
	getcwd(working_dir, 1024);
	if (working_dir == NULL)
		printf("grrrr\n");
	else
		printf("pwd : %s\n", working_dir);
}

