
#include "minishell.h"
#include "minishell_louis.h"


int	parsing(t_data *data, const char *input)
{
	t_info	*info;
	int		function_return;
	
	info = NULL;
	if (ft_check_open_quote(input))
		return (SYNTAX_QUOTE_ERROR);
	else if (!ft_check_empty_line(input, 0))
		return (FUNCTION_SUCCESS);
	else
	{
		info = create_info(info);
		if (!info)
			return (ft_error(MEMORY_ERROR_NB)); //besoin d'effacer qq chose aussi
		// printf(BLUE"\nTOKENISE & CHECK SYNTAX\n"NC);
		function_return = ft_tokenise(input, info);
		if (function_return == LINE_IS_EMPTY)
			return (FUNCTION_SUCCESS); // faut free des trucs tho
		if (function_return != FUNCTION_SUCCESS)
			return (ft_error(function_return));
		if (!ft_check_syntax_with_tokens(info->tokens))
			ft_error(SYNTAX_TOKEN_ERROR);
		else
		{
			// ft_display_lexer(*info);
			// printf(BLUE"\nDEL QUOTES\n"NC);
			if (ft_del_quotes(info) != FUNCTION_SUCCESS) 
				return (MEMORY_ERROR_NB);
			// ft_display_lexer(*info);
			// printf(BLUE"\nEXPAND\n"NC);
			ft_expand(info, data->envp); //add secu
			//ft_display_lexer(*info);
			// printf(BLUE"\nJOIN\n"NC);
			ft_join_nodes(info->tokens);
			// ft_display_lexer(*info);
			// printf(BLUE"\nINTERPRETE\n"NC);
			function_return = ft_interprete(info, data); // attention, on va avoir une verif a faire
			// if (function_return != FUNCTION_SUCCESS)
			// 	return (ft_error(function_return, data, info));
		}
		ft_clean_info_bis(&info);
	}
	(void)data;
	return (FUNCTION_SUCCESS);
}

