/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/08/28 18:20:24 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	parse_envp(t_data *data, char **envp)
// {
// 	int		i;

// 	i = 0;
// 	if (!envp[0])
// 		return (0);
// 	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
// 		i++;
// 	if (envp[i])
// 	{
// 		data->path = ft_split(&envp[i][5], ':');
// 		if (data->path == NULL)
// 			return (-1);
// 	}
// 	return (0);
// }


int	main(int argc, char **argv, char **envp)
{
	(void) argv;
	(void) envp;
	if (argc == 1)
	{
		prompt();
		return (0);
	}
	return (perror("Error : Please launch minishell with no additional argument"), -1);
}
