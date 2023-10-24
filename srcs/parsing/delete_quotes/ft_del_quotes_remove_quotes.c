#include "minishell.h"
#include "minishell_louis.h"

bool	ft_check_empty_line_quote(const char *str, int i)
{
	i++;
	while (str[i])
	{
		if (str[i] >= 32 && str[i + 1] != 0)
			return (true);
		i++;
	}
	return (false);
}

int	ft_remove_quotes(t_list *list, char quote)
{
	t_token	*current_token;
	char	*curr_word;

	current_token = (t_token *)list->content;
	if (!ft_check_empty_line_quote(current_token->string, 0))
		curr_word = ft_strdup("\0");
	else if (quote == DOUBLE_QUOTE)
	{
		current_token->quote = double_q;
		curr_word = ft_strtrim(current_token->string, "\"");
	}
	else
	{
		current_token->quote = simple_q;
		curr_word = ft_strtrim(current_token->string, "'");
	}
	if (!curr_word)
		return (MEMORY_ERR_NB);
	free(current_token->string);
	current_token->string = curr_word;
	return (FUNCTION_SUCCESS);
}
