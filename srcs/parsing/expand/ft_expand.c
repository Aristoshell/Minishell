#include "minishell.h"
#include "minishell_louis.h"

int	ft_expand(t_info *info, t_envlist *envp, t_data *data)
{
	t_list	*list;
	t_token	*curr_token;
	int		dollar_loc;

	list = info->tokens;
	dollar_loc = 0;
	while (list)
	{
		curr_token = (t_token *)list->content;
		if (curr_token->type == type_word && (curr_token->quote != simple_q) && !curr_token->empty_node)
		{
			dollar_loc = ft_strchr_int(curr_token->string, '$');
			//printf("omg\n");
			if (dollar_loc >= 0 && !(curr_token->string[0] == '$' && (curr_token->string[1] == 0 || curr_token->string[1] == '$')))
			{
				if (ft_detatch_expand(list, dollar_loc) != FUNCTION_SUCCESS)
					return (MEMORY_ERROR_NB);
				if (curr_token->expand) //encore utile ?
					ft_expand_val(list, envp, data); // attention checker le retour
			}
		}
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}
