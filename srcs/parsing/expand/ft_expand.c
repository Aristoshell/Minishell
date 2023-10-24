#include "minishell.h"
#include "minishell_louis.h"

int	ft_expand(t_envlist *envp, t_data *data)
{
	t_list			*list;
	t_token			*curr_token;
	int				dollar_loc;
	t_token_type	prev_type;

	list = data->tokens;
	dollar_loc = 0;
	prev_type = type_default;
	while (list)
	{
		curr_token = (t_token *)list->content;
		if (curr_token->type == type_word && prev_type != type_heredoc && (curr_token->quote != simple_q) && !curr_token->empty_node)
		{
			dollar_loc = ft_strchr_int(curr_token->string, '$');
			if (dollar_loc >= 0 && !(curr_token->string[0] == '$' && (curr_token->string[1] == 0 || curr_token->string[1] == '$')))
			{
				if (ft_detatch_expand(list, dollar_loc) != FUNCTION_SUCCESS)
					return (MEMORY_ERR_NB);
				if (curr_token->expand /* encore utile ?*/ && ft_expand_val(list, envp, data)) 
					return (MEMORY_ERR_NB);
			}
		}
		if (!curr_token->empty_node)
			prev_type = curr_token->type;
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}
