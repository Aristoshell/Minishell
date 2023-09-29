/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	parsing(t_data *data, const char *input)
{
	t_info	*info;
	int		function_return;
	
	info = NULL;
	if (!check_syntax(input)) // faudra juste appeler check quotes en fait
			return (SYNTAX_QUOTE_ERROR);
	else
	{
		info = create_info(info);
		if (!info)
			return (ft_error(MEMORY_ERROR_NB)); //besoin d'effacer qq chose aussi
		function_return = ft_lexer(input, info);
		if (function_return != FUNCTION_SUCCESS)
			return (ft_error(function_return));
		if (!ft_check_syntax_with_tokens(*info))
			ft_error(SYNTAX_TOKEN_ERROR);
		else
		{
			//ft_display_lexer(*info);
			function_return = ft_parser(info, data); // attention, on va avoir une verif a faire
			//if (function_return != FUNCTION_SUCCESS)
			//	return (ft_error(function_return, data, info));
		}
		ft_clean_info_bis(&info);
	}
	return (FUNCTION_SUCCESS);
}

