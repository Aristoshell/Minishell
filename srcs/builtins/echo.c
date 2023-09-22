/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 22:56:57 by marine            #+#    #+#             */
/*   Updated: 2023/09/22 17:08:46 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* appeler avec n = 1 pour echo normal et n = 0 pour echo -n*/

void	echo(char **argv, int n)
{
	int	i;

	i = 1;
	while (argv[i] && argv[i][0])
	{
		ft_printf(1, "%s", argv[i]);
		i++;
		if (argv[i] && argv[i][0])
			ft_printf(1, " ");
	}
	if (n == 0)
		ft_printf(1, "\n");
}

// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	//echo(argv, 1);
// 	echo(argv, 0);
// 	return (0);
// }
