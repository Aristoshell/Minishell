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

int	ft_del_quotes(t_data *data)
{
	t_list	*list;
	t_token	*curr_tok;
	t_list	*prev;
	int		check;

	list = data->tokens;
	prev = NULL;
	while (list)
	{
		curr_tok = (t_token *)list->content;
		if (curr_tok->type == type_word)
		{
			if (ft_split_quotes(list) != FUNCTION_SUCCESS)
				return (MEMORY_ERR_NB);
			if (curr_tok->quote)
			{
				check = ft_remove_quotes(list, curr_tok->string[0]);
				if (check == MEMORY_ERR_NB)
					return (MEMORY_ERR_NB);
			}
		}
		prev = list;
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}
