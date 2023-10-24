
#include "minishell.h"
#include "minishell_louis.h"

int	ft_init_token(t_token *new_token, const char *input, int *i)
{
	new_token->string = NULL;
	new_token->string = get_token_val(input, i);
	if (!new_token->string)
		return (MEMORY_ERR_NB);
	new_token->type = get_token_type(new_token->string);
	new_token->expand = false;
	new_token->join_with_next = false;
	new_token->quote = no_q;
	new_token->empty_node = false;
	new_token->redir_file = false;
	return (FUNCTION_SUCCESS);
}

void	ft_clean_token(t_token *token)
{
	if (token)
	{
		if (token->string)
		{
			free(token->string);
			token->string = NULL;
		}
		free(token);
		token = NULL;
	}
}

int	ft_tokenise(const char *input, t_data *data)
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
			return (MEMORY_ERR_NB);
		if (ft_init_token(new_token, input, &i) != FUNCTION_SUCCESS)
			return (free(new_token), new_token = NULL, MEMORY_ERR_NB);
		new_node = ft_lstnew((void *)new_token);
		if (!new_node)
		{
			ft_clean_token(new_token);
			ft_lstclear(&(data)->tokens, (void *)ft_clean_token);
			return (new_token = NULL, data->tokens = NULL, MEMORY_ERR_NB);
		}
		ft_lstadd_back(&data->tokens, new_node);
	}
	return (FUNCTION_SUCCESS);
}
