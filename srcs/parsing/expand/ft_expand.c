#include "minishell.h"
#include "minishell_louis.h"

int	ft_expand(t_envlist *envp, t_data *data)
{
	t_list			*list;
	t_token_type	prev_type;

	list = data->tokens;
	data->dollar_loc = 0;
	prev_type = type_default;
	while (list)
	{
		data->curr_token = (t_token *)list->content;
		if (data->curr_token->type == type_word && prev_type != type_heredoc
			&& (data->curr_token->quote != simple_q))
		{
			data->dollar_loc = ft_strchr_int(data->curr_token->string, '$');
			if (data->dollar_loc >= 0)
			{
				if (ft_detatch_expand(list, data->dollar_loc))
					return (MEMORY_ERR_NB);
				if (data->curr_token->expand && ft_expand_val(list, envp, data))
					return (MEMORY_ERR_NB);
			}
		}
		prev_type = data->curr_token->type;
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}

	// printf("EXPAND\n");
	// ft_display_lexer(*data);