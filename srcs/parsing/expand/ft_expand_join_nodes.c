
#include "minishell.h"
#include "minishell_louis.h"

int	ft_join_nodes(t_list *list, t_data *data)
{
	char	*join;
	t_token	*next_token;
	t_list	*next_node;
	t_list	*save;

	while (list)
	{
		data->curr_token = (t_token *)list->content;
		if (!data->curr_token->join_with_next)
			list = list->next;
		else
		{
			next_node = list->next;
			if (next_node)
				next_token = (t_token *)next_node->content;
			if (!data->curr_token->string && (!next_node || !next_token->string))
			{
				save = list->next->next;
				ft_lstdelone(list->next, (void *)ft_clean_token);
				list->next = save;
				data->curr_token->join_with_next = false;
			}
			else
			{
				join = ft_strjoin_ms(data->curr_token->string, next_token->string);
				if (!join)
					return (MEMORY_ERR_NB);
				free(data->curr_token->string);
				data->curr_token->string = join;
				data->curr_token->join_with_next = next_token->join_with_next;
				save = list->next->next;
				ft_lstdelone(list->next, (void *)ft_clean_token);
				list->next = save;
			}
		}
	}
	return (FUNCTION_SUCCESS);
}

	// printf("JOIN NODES\n");
	// ft_display_lexer(*data);