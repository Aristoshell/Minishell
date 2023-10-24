#include "minishell.h"
#include "minishell_louis.h"

int	ft_need_detach(char *str)
{
	int		i;
	int		equals;

	i = 1;
	if (str[1] == '?' )
	{
		if (!str[2])
			return(0);
		return (2);
	}
	equals = ft_strchr_int(str, '=');
	if (equals > 0)
		return (equals);
	else
	{
		while (str[i])
		{
			if (ft_is_space(str[i]) || ft_is_dollar(str[i]))
				return (i);
			i++;
		}
	}
	return (0);
}

int	ft_suppress_dollar(t_token *curr_token)
{
	char	*truncate;

	if (curr_token->string[0] == '$')
	{
		curr_token->expand = true;
		truncate = ft_strtrim(curr_token->string, "$");
		if (!truncate)
			return (MEMORY_ERR_NB);
		free(curr_token->string);
		curr_token->string = truncate;
		return (FUNCTION_SUCCESS);
	}
	return (FUNCTION_SUCCESS);
}

// int	ft_special_expand(t_list *list, int i)
// {
// 	t_token	*current_token;
// 	t_token	*next;
// 	char	*truncate;

// 	current_token = (t_token *)list->content;
// }

int	ft_detatch_expand(t_list *list, int i)
{
	t_token	*current_token;
	t_token	*next;
	char	*truncate;

	current_token = (t_token *)list->content;
	if (i == 0)
		i = ft_need_detach(current_token->string);
	if (i) //si on doit détacher qq chose
	{
		if (ft_insert_next_node(i, list) != FUNCTION_SUCCESS)
			return (MEMORY_ERR_NB);
		if (current_token->join_with_next)
		{
			next = (t_token *)list->next->content;
			next->join_with_next = true;
		}
		current_token->join_with_next = true; //important de le garder apres
		truncate = ft_substr(current_token->string, 0, i);
		//printf("Truncate = %s\n", truncate);
		if (!truncate)
			return (MEMORY_ERR_NB);
		free(current_token->string);
		current_token->string = truncate;
	}
	if (ft_suppress_dollar(current_token))
		return (MEMORY_ERR_NB);
	return (FUNCTION_SUCCESS);
}
