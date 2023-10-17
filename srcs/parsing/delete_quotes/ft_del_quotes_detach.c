#include "minishell.h"
#include "minishell_louis.h"

char	*ft_change_current_str(t_token *current_token, int i, char quote)
{
	char	*curr_word;

	current_token->join_with_next = true;
	curr_word = ft_substr(current_token->string, 0, i);
	if (!curr_word)
		return (MEMORY_ERROR_PT);
	if (current_token->string[0] == quote)
		current_token->quote = true_q;
	return (curr_word);
}

// on aura peut etre un segfault ici car on check pas si /0
void	ft_get_i(char quote, char *string, int *i)
{
	*i += 1;
	while (string[*i] != quote)
		*i += 1;
	*i += 1;
}

int	ft_insert_next_node(int i, t_list *list)
{
	t_token	*curr_token;
	t_token	*new_token;
	char	*new_word;
	t_list	*new;

	curr_token = (t_token *)list->content;
	new_word = ft_substr(curr_token->string, i, ft_strlen(curr_token->string));
	if (!new_word)
		return (MEMORY_ERROR_NB);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (MEMORY_ERROR_NB);
	new_token->string = new_word;
	new_token->type = type_word;
	new_token->expand = false;
	new_token->join_with_next = false;
	new_token->quote = false;
	new_token->empty_node = false;
	new_token->redir_file = false;
	new = ft_lstnew((void *)new_token);
	if (!new)
		return (MEMORY_ERROR_NB);
	new->next = list->next;
	list->next = new;
	return (FUNCTION_SUCCESS);
}

int	ft_detach_quotes(int i, t_list *list, char quote)
{
	char	*curr_word;
	t_token	*current_token;

	curr_word = NULL;
	current_token = (t_token *)list->content;
	if (i == 0) //on est dans une quote + c'est la premiere
	{
		ft_get_i(quote, current_token->string, &i);
		if (current_token->string[0] == quote)
			current_token->quote = true_q;
		if (!current_token->string[i]) // si jamais ya rien a split, on return
			return (FUNCTION_SUCCESS);
	}
	if (ft_insert_next_node(i, list) != FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	curr_word = ft_change_current_str(current_token, i, quote);
	if (!curr_word)
		return (MEMORY_ERROR_NB);
	free(current_token->string);
	current_token->string = curr_word;
	return (FUNCTION_SUCCESS);
}

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
