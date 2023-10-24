
#include "minishell.h"
#include "minishell_louis.h"

int	parsing(t_data *data, const char *input)
{
	if (ft_check_open_quote_bool(input) || !ft_check_empty_line(input, 0))
		return (FUNCTION_SUCCESS);
	// printf("Tokenisation\n");
	if (ft_tokenise(input, data))
		return (MEMORY_ERR_NB);
	// ft_display_lexer(*data);
	if (ft_check_syntax_with_tokens(data->tokens))
	{
		// if (ft_del_quotes(data) || ft_expand(data->envp, data)
		// 	|| ft_join_nodes(data->tokens) || ft_interprete(data))
		// {
		// 	ft_lstclear(&(data)->tokens, (void *)ft_clean_token);
		// 	data->tokens = NULL;
		// 	return (MEMORY_ERR_NB);
		// }
		// printf("Del quotes\n");
		ft_del_quotes(data);
		// ft_display_lexer(*data);
		// printf("Expand\n");
		ft_expand(data->envp, data);
		// ft_display_lexer(*data);
		// printf("Join\n");
		ft_join_nodes(data->tokens);
		// ft_display_lexer(*data);
		// printf("Interprete\n");
		ft_interprete(data);
		// ft_display_lexer(*data);
	}
	ft_lstclear(&(data)->tokens, (void *)ft_clean_token);
	// printf("tokens cleaned\n");
	data->tokens = NULL;
	return (FUNCTION_SUCCESS);
}
