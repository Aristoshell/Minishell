#include "minishell.h"
#include "minishell_louis.h"

/* This function checks for each token whether 
there are quotes or not. 
If applicable, a function will check wether there 
are more parts that need to be separated or not */

int	ft_split_quotes(t_list *list)
{
	t_token	*current_token;
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	current_token = (t_token *)list->content;
	while (current_token->string[i] && !quote)
	{
		quote = ft_is_quote(current_token->string[i]);
		if (quote)
			return (ft_detach_quotes(i, list, quote));
		i++;
	}
	return (FUNCTION_SUCCESS);
}

/* This function aims to delete the quotes from the tokens :
1) splitting nodes that have several parts using quotes as separator
2) removing the quotes from the strings of nodes needing it, specifying
wether the string used to have  simple or double quotes using a boolean */

int	ft_del_quotes(t_data *data)
{
	t_list	*list;
	t_token	*curr_tok;
	int		check;

	list = data->tokens;
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
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}

	// printf("DEL QUOTES\n");
	// ft_display_lexer(*data);