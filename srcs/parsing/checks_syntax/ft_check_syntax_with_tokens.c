
#include <minishell.h>

int	ft_check_message(t_token *cur_node, t_list *tok, t_token *next_node, int i)
{
	if (cur_node->type == type_pipe)
	{
		if (i == 0 || !tok->next || next_node->type == type_pipe)
			return (ft_dprintf(STDERR_FILENO, D_ER_SYN_PIPE), 1);
	}
	else if (cur_node->type >= type_from)
	{
		if (!tok->next)
			return (ft_dprintf(STDERR_FILENO, D_ER_SYN_NL), 1);
		else if (next_node->type == type_pipe)
			return (ft_dprintf(STDERR_FILENO, D_ER_SYN_PIPE), 1);
		else if (next_node->type == type_from)
			return (ft_dprintf(STDERR_FILENO, D_ER_SYN_FROM), 1);
		else if (next_node->type == type_heredoc)
			return (ft_dprintf(STDERR_FILENO, D_ER_SYN_HERED), 1);
		else if (next_node->type == type_to)
			return (ft_dprintf(STDERR_FILENO, D_ER_SYN_TO), 1);
		else if (next_node->type == type_heredoc)
			return (ft_dprintf(STDERR_FILENO, D_ER_SYN_APPEND), 1);
	}
	return (FUNCTION_SUCCESS);
}

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
		if (ft_check_message(current_node, token, next_node, i))
			return (false);
		i++;
		token = token->next;
	}
	return (true);
}
