/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:57:48 by marine            #+#    #+#             */
/*   Updated: 2023/07/06 10:42:32 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_new_lexer_node(char *input, int index)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (new_node == NULL)
		return (NULL);
	new_node->type = check_type(input);
	if (new_node->type == word)
		new_node->word = input;
	else
		new_node->word = NULL;
	new_node->index = index;
	new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_lexer	*ft_last_lexer_node(t_lexer *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}
// t_lexer	*ft_scndlast_lexer_node(t_lexer *node)
// {
// 	if (node == NULL)
// 		return (NULL);
// 	while (node->next->next != NULL)
// 		node = node->next;
// 	return (node);
// }

void	ft_node_lexer_add_back(t_lexer **node, t_lexer *new)
{
	t_lexer	*temp_last;

	if (*node != NULL)
	{
		temp_last = ft_last_lexer_node(*node);
		temp_last->next = new;
	}
	else
		*node = new;
}

void	ft_print_lexer(t_lexer	*node)
{
	while (node)
	{
		printf("Index : %d, type : %u, word : |%s|\n", node->index, node->type, node->word);
		if (!node->next)
			return ;
		*node = *node->next;
	}
}
