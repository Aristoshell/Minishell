/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/09/23 01:47:37 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_data *data, t_info *info, char *input)
{
	int	function_return;

	if (!check_syntax(input))
			return (SYNTAX_ERROR);
	else
	{
		function_return = ft_lexer(input, info);
		if (function_return != FUNCTION_SUCCESS)
			return (ft_error(function_return, data, info));
		ft_display_lexer(*info);
		//function_return = parser(info); // attention, on va avoir une verif a faire
		//if (function_return != FUNCTION_SUCCESS)
		//	return (ft_error(function_return, data, info));
		//ft_reinit_info(info);
	}
	return (FUNCTION_SUCCESS);
}

