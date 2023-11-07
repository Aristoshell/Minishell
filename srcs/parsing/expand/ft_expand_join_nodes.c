
#include "minishell.h"
#include "minishell_louis.h"

int	ft_join_nodes(t_list *list, t_data *data)
{
	t_token	*current_token;
	char	*join;
	t_token	*next_token;
	t_list	*next_node;
	t_list 	*save;

	(void)data;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (!current_token->join_with_next) //passer les non join
			list = list->next;
		else
		{
			next_node = list->next;
			if (next_node)
				next_token = (t_token *)next_node->content;
			if (!current_token->string && (!next_node || !next_token->string))
			{
				save = list->next->next;
				ft_lstdelone(list->next, (void *)ft_clean_token);
				list->next = save;
				current_token->join_with_next = false;
			}
			else
			{
				join = ft_strjoin_ms(current_token->string, next_token->string);
				if (!join)
					return (MEMORY_ERR_NB);
				free(current_token->string);
				current_token->string = join;
				current_token->join_with_next = next_token->join_with_next;
				save = list->next->next;
				ft_lstdelone(list->next, (void *)ft_clean_token);
				list->next = save;
			}
		}
	}
	// printf("JOIN NODES\n");
	// ft_display_lexer(*data);
	return (FUNCTION_SUCCESS);
}
