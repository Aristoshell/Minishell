/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/07/28 00:27:38 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	*input;
	char	quote;
	//t_lexer	*root;
	char *end_ofquote;

	quote = 0;
	end_ofquote = NULL;
	//root = NULL;
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
			quote = check_open_quote(input);
			while (quote != 0)
			{
				if (end_ofquote != NULL)
					free (end_ofquote);
				end_ofquote = close_quote(quote);
				char *tmp = ft_strdup(input);
				free(input);
				input = ft_strjoin(tmp, end_ofquote);
				quote = check_open_quote(input);
			}
			//root = lexer(input, &root);
			//ft_print_lexer(root);
			printf("t'as dit \"%s\"\n", input);
			//ft_lexer_clear(&root);
			free(input);
		}
	}
}
