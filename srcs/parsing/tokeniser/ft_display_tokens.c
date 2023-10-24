
#include "minishell.h"
#include "minishell_louis.h"

void	ft_display_lexer(t_data data)
{
	t_token	*curr_token;

	while (data.tokens)
	{
		curr_token = (t_token *)data.tokens->content;
		ft_dprintf(STDERR_FILENO, "New	");
		ft_dprintf(STDERR_FILENO, "str : %s, ", curr_token->string);
		ft_dprintf(STDERR_FILENO, "          ");
		ft_dprintf(STDERR_FILENO, "type : %d, ", curr_token->type);
		ft_dprintf(STDERR_FILENO, "expand : %d, ", curr_token->expand);
		ft_dprintf(STDERR_FILENO, "join : %d, ", curr_token->join_with_next);
		ft_dprintf(STDERR_FILENO, "in quote : %d, ", curr_token->quote);
		ft_dprintf(STDERR_FILENO, "empty : %d\n", curr_token->empty_node);
		data.tokens = data.tokens->next;
	}
}
