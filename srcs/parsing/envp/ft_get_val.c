/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_val.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:08:58 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 18:58:19 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(char *line)
{
	char	*val;
	int		size;

	size = ft_strlen(line);
	val = malloc((size + 1) * sizeof(char));
	if (!val)
		return (MEMORY_ERROR_PT); // attention a l'erreur renvoyee
	ft_strlcpy(val, line, (size + 1));
	return (val);
}
