#include "minishell.h"
#include "minishell_louis.h"

int	ft_need_detach(char *str)
{
	int		i;

	i = 1;
	//rajouter une condition qui va checker avant quon n'a pas de = juste apres le $
	if (str[1] == '?')
	{
		if (!str[2])
			return (0);
		return (2);
	}
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (i);
		i++;
	}
	return (0);
}

int	ft_suppress_dollar(t_token *curr_token, t_list *list)
{
	char	*truncate;
	
	if (curr_token->string[0] == '$')
	{
		if (curr_token->string[1] == '\0' && (!list->next))
				return (FUNCTION_SUCCESS);
		curr_token->expand = true;
		truncate = ft_strdup(&curr_token->string[1]);
		if (!truncate)
			return (MEMORY_ERR_NB);
		free(curr_token->string);
		curr_token->string = truncate;
	}
	return (FUNCTION_SUCCESS);
}

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
		if (!truncate)
			return (MEMORY_ERR_NB);
		free(current_token->string);
		current_token->string = truncate;
	}
	return (ft_suppress_dollar(current_token, list));
}
