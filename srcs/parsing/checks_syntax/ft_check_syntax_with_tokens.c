
#include <minishell.h>

bool	ft_check_syntax_with_tokens(t_list *token)
{
	t_token		*current_node;
	t_token		*next_node;
	int			i;

	i = 0;
	next_node = NULL;
	while (token)
	{
		current_node = (t_token *)token->content;
		if (token->next)
			next_node = (t_token *)token->next->content;
		if (current_node->type == type_pipe)
		{
			if (i == 0 || !token->next || next_node->type == type_pipe)
				return (false);
		}
		else if (current_node->type >= type_from)
		{
			if (!token->next || next_node->type != type_word)
				return (false);
		}
		i++;
		token = token->next;
	}
	return (true);
}
