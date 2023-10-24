
#include <minishell.h>

int	ft_check_message(t_token *current_node, t_list *token, t_token *next_node, int i)
{
	if (current_node->type == type_pipe)
	{
		if (i == 0 || !token->next || next_node->type == type_pipe)
			return (SYNTAX_PIPE_ERROR);
	}
	else if (current_node->type >= type_from)
	{
		if (!token->next)
			return (SYNTAX_NEWL_ERROR);
		else if (next_node->type == type_pipe)
			return (SYNTAX_PIPE_ERROR);
		else if (next_node->type == type_from)
			return (SYNTAX_FROM_ERROR);
		else if (next_node->type == type_heredoc)
			return (SYNTAX_HERED_ERROR);
		else if (next_node->type == type_to)
			return (SYNTAX_TO_ERROR);
		else if (next_node->type == type_heredoc)
			return (SYNTAX_APPND_ERROR);
	}
	return (FUNCTION_SUCCESS);
}

bool	ft_check_syntax_with_tokens(t_list *token)
{
	t_token		*current_node;
	t_token		*next_node;
	int			i;
	int			check;

	i = 0;
	next_node = NULL;
	while (token)
	{
		current_node = (t_token *)token->content;
		if (token->next)
			next_node = (t_token *)token->next->content;
		check = ft_check_message(current_node, token, next_node, i);
		if (check)
			return (ft_error(check, NULL), false);
		i++;
		token = token->next;
	}
	return (true);
}
