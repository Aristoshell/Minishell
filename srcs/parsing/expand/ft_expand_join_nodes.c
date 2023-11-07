
#include "minishell.h"
#include "minishell_louis.h"

int	ft_join_nodes(t_list *list, t_data *data)
{
	t_token	*current_token;
	char	*join;
	t_token	*next_token;
	t_list	*next_node;

	(void)data;
	while (list)
	{
		current_token = (t_token *)list->content;
		while (list && !current_token->join_with_next) //passer les non join
		{
			list = list->next;
			if (list)
				current_token = (t_token *)list->content;
		}
		while (list && current_token->join_with_next) 
		{
			next_node = list->next;
			if (next_node)
				next_token = (t_token *)next_node->content;
			if (next_node)
			{
				join = ft_strjoin(current_token->string, next_token->string);
				if (!join)
					return (MEMORY_ERR_NB);
				free(current_token->string);
				current_token->string = join;
				current_token->join_with_next = next_token->join_with_next;
				t_list *save;
				save = list->next->next;
				ft_lstdelone(list->next, (void *)ft_clean_token);
				list->next = save;
			}
			list = list->next;
		}
	}
	// printf("JOIN NODES\n");
	// ft_display_lexer(*data);
	return (FUNCTION_SUCCESS);
}
