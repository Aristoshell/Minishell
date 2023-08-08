/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 18:57:48 by marine            #+#    #+#             */
/*   Updated: 2023/08/08 16:05:44 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*ft_new_lexer_node(char *input, int index)
{
	t_lexer	*new_node;

	(void) index;
	new_node = malloc(sizeof(t_lexer));
	if (new_node == NULL)
		return (NULL);
	new_node->type = check_type(input);
	new_node->word = input;
	//new_node->index = index;
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

void	ft_print_lexer(t_lexer	**node)
{
	t_lexer	*temp;

	temp = *node;
	while (temp)
	{
		printf("type : %u, word : |%s|\n", temp->type, temp->word);
		if (!temp->next)
			return ;
		temp = temp->next;
	}
}
