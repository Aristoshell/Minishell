#include "minishell.h"
#include "minishell_louis.h"

void	ft_change_join_bool(t_list *prev, t_list *curr)
{
	t_token	*curr_token;
	t_token	*prev_token;

	curr_token = (t_token *)curr->content;
	prev_token = (t_token *)prev->content;
	if (prev_token->join_with_next && !curr_token->join_with_next)
		prev_token->join_with_next = false;
}

int	ft_del_quotes(t_info *info)
{
	t_list	*list;
	t_token	*curr_tok;
	t_list	*prev;

	list = info->tokens;
	prev = NULL;
	while (list)
	{
		curr_tok = (t_token *)list->content;
		if (curr_tok->type == type_word)
		{
			if (ft_split_quotes(list) != FUNCTION_SUCCESS)
				return (MEMORY_ERROR_NB); // attention, mal clean
			if (curr_tok->quote
				&& ft_remove_quotes(list, curr_tok->string[0]) == LINE_IS_EMPTY)
			{
				if (prev)
					ft_change_join_bool(prev, list);
				curr_tok->empty_node = true;
			}
		}
		prev = list;
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}
