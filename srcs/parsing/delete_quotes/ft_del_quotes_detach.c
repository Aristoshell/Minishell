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

void	ft_get_length(char quote, char *string, int *i)
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
	nw_tok->empty_node = false;// a tej
	nw_tok->redir_file = false;
	new = ft_lstnew((void *)nw_tok);
	if (!new)
		return (free(nw_word), nw_word = NULL, free(nw_tok), nw_tok = NULL, 2);
	new->next = list->next;
	list->next = new;
	return (FUNCTION_SUCCESS);
}
/* This function aims to detach tokens that have several parts.
ex: a token with a string "hihi"ahah'omgg'yeaah) will be detatched in 4 different tokens :
		- "hihi" (enum quote = true)
		- ahah (enum quote = no)
		- 'omg' (enum quote = true)
		- yeaah (enum quote = no) 
- If the quote is located at the begining, the ft_get_length 
will check where the closing quote is located to check if another parts needs
to be detatched or not. In both case, the node will have its quote enum to true.
If the token ends at the closing quote, there is no need to continue, and the function returns
- The function continues if the quote was not in the first part or if there
 is another part after quotes, to separate the parts with insert new node
- After the new node is created, the current node will get his extra part
that has been aded in a new node removed with the function change current string*/

int	ft_detach_quotes(int i, t_list *list, char quote)
{
	char	*curr_word;
	t_token	*current_token;

	curr_word = NULL;
	current_token = (t_token *)list->content;
	if (i == 0)
	{
		ft_get_length(quote, current_token->string, &i);
		if (current_token->string[0] == quote)
			current_token->quote = true_q;
		if (!current_token->string[i])
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
