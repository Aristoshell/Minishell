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
	t_token	*curr_tok;
	t_token	*nw_tok;
	char	*nw_word;
	t_list	*new;

	curr_tok = (t_token *)list->content;
	nw_word = ft_substr(curr_tok->string, i, ft_strlen(curr_tok->string));
	if (!nw_word)
		return (MEMORY_ERR_NB);
	nw_tok = malloc(sizeof(t_token));
	if (!nw_tok)
		return (free(nw_word), nw_word = NULL, MEMORY_ERR_NB);
	nw_tok->string = nw_word;
	nw_tok->type = type_word;
	nw_tok->expand = false;
	nw_tok->join_with_next = false;
	nw_tok->quote = false;
	nw_tok->empty_node = false;
	nw_tok->redir_file = false;
	new = ft_lstnew((void *)nw_tok);
	if (!new)
		return (free(nw_word), nw_word = NULL, free(nw_tok), nw_tok = NULL, 2);
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
		return (MEMORY_ERR_NB);
	curr_word = ft_change_current_str(current_token, i, quote);
	if (!curr_word)
		return (MEMORY_ERR_NB);
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
		{
			if (ft_detach_quotes(i, list, quote))
				return (MEMORY_ERR_NB);
			return (FUNCTION_SUCCESS); // pourrait etre racourci avec return la fonction direct
		}
		i++;
	}
	return (FUNCTION_SUCCESS);
}
