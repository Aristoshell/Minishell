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
	while (list)
	{
		curr_token = (t_token *)list->content;
		if (curr_token->type == type_word && prev_type != type_heredoc && (curr_token->quote != simple_q))
		{
			dollar_loc = ft_strchr_int(curr_token->string, '$');
			if (dollar_loc >= 0)
			{
				if (ft_detatch_expand(list, dollar_loc) != FUNCTION_SUCCESS)
					return (MEMORY_ERR_NB);
				if (curr_token->expand && ft_expand_val(list, envp, data))
					return (MEMORY_ERR_NB);
			}
		}
		prev_type = curr_token->type;
		list = list->next;
	}
	// printf("EXPAND\n");
	// ft_display_lexer(*data);
	return (FUNCTION_SUCCESS);
}
