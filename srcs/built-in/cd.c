/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:56:51 by marine            #+#    #+#             */
/*   Updated: 2023/07/23 00:06:38 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
#include <unistd.h>

void	cd(char *path)
{
	printf("%s\n", path);
	if (chdir(path) != 0)
		return (perror("Error"));
}

int	main(int argc, char **argv)
{
	(void) argc;
	cd(argv[1]);
	return (0);
}
