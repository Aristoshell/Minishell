#include "minishell.h"
#include "minishell_louis.h"

int	ft_expand(t_info *info, t_envlist *envp)
{
	t_list	*list;
	t_token	*current_token;
	int		dollar_loc;

	list = info->tokens;
	dollar_loc = 0;
	while (list)
	{
		current_token = (t_token *)list->content;
		if (current_token->type == type_word
			&& (current_token->quote != simple_q))
		{
			dollar_loc = ft_strchr_int(current_token->string, '$');
			if (dollar_loc >= 0)
			{
				if (ft_detatch_expand(list, dollar_loc) != FUNCTION_SUCCESS)
					return (MEMORY_ERROR_NB);
				if (current_token->expand)
					ft_expand_val(list, envp); // attention checker le retour
			}
		}
		list = list->next;
		(void) envp;
	}
	return (FUNCTION_SUCCESS);
}
