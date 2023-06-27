/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/06/27 18:04:23 by marine           ###   ########.fr       */
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
		if (strcmp(input, "exit") == 0)
		{
			free(input);
			clear_history();
			return ;
		}
		if (input != 0)
			printf("t'as dit \"%s\"\n", input);
	}
}
