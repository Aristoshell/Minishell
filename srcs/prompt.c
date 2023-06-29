/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/06/29 18:45:11 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline("aristoshell$ ");
		add_history(input);
		if (!input || ft_strncmp(input, "exit", ft_strlen(input) + 1) == 0)
		{
			printf("exit\n");
			free(input);
			clear_history();
			return ;
		}
		if (input && input[0] != 0)
		{
			printf("t'as dit \"%s\"\n", input);
			free(input);
		}
	}
}
