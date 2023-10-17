
#include "minishell.h"
#include "minishell_louis.h"

int	ft_init_token(t_token *new_token, const char *input, int *i)
{
	new_token->string = NULL;
	new_token->string = get_token_val(input, i);
	if (!new_token->string)
		return (MEMORY_ERROR_NB); //free des trucs aussi
	new_token->type = get_token_type(new_token->string);
	new_token->expand = false;
	new_token->join_with_next = false;
	new_token->quote = no_q;
	new_token->empty_node = false;
	new_token->redir_file = false;
	return (FUNCTION_SUCCESS);
}

int	ft_tokenise(const char *input, t_info *info)
{
	int		i;
	t_list	*new_node;
	t_token	*new_token;

	i = 0;
	while (input[i])
	{
		if (!ft_check_empty_line(input, i))
			break ;
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (MEMORY_ERROR_NB);
		if (ft_init_token(new_token, input, &i) != FUNCTION_SUCCESS)
			return (MEMORY_ERROR_NB); //penser a bien free
		new_node = ft_lstnew((void *)new_token);
		if (!new_node)
			return (MEMORY_ERROR_NB);
		ft_lstadd_back(&info->tokens, new_node);
	}
	return (FUNCTION_SUCCESS);
}
