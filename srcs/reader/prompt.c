/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/07/28 12:08:36 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*input;
	char	*tmp;

	//t_lexer	*root;
	//root = NULL;
	tmp = NULL;
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
			tmp = manage_quote(input);
			input = ft_strdup(tmp);
			free(tmp);
			//root = lexer(input, &root);
			//ft_print_lexer(root);
			printf("t'as dit \"%s\"\n", input);
			//ft_lexer_clear(&root);
			free(input);
		}
	}
}
