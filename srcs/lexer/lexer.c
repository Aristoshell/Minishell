/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/08/07 19:07:28 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_type	check_type(char *input)
{
	if (input[0] == '|' && input[1] == 0)
		return (token_pipe);
	else if (input[0] == '<' && input[1] == 0)
		return (token_in);
	else if (input[0] == '>' && input[1] == 0)
		return (token_out);
	else
		return (word);
}

t_lexer	*lexer(char *input, t_lexer **root)
{
	t_lexer	*new;
	int		i;
	int		index;

	new = NULL;
	i = 0;
	index = 0;
	while (input[i])
	{
		new = ft_new_lexer_node(ft_split_lexer(input, &i), index);
		if (new == NULL)
			return (ft_lexer_clear(root), NULL);
		ft_node_lexer_add_back(root, new);
		index++;
	}
	return (*root);
}

// void check_quote(char *input)
// {
// 	int i;
// 	int count_s_quote;
// 	int count_d_quote;

// 	i = 0;
// 	count_s_quote = 0;
// 	count_d_quote = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'')
// 			count_s_quote++;
// 		else if (input[i] == '\"')
// 			count_d_quote++;
// 		i++;
// 	}
// 	printf("nb simple quote \"%d\"\n", count_s_quote);
// 	printf("nb double quote \"%d\"\n", count_d_quote);
// }
