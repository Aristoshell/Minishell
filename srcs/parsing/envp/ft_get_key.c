/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:57:00 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 01:57:02 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

char	*ft_get_key(char *line, int sep)
{
	char	*key;
	int		size;

	if (sep < 0)
		size = ft_strlen(line);
	else
		size = sep;
	key = malloc((size + 1) * sizeof(char));
	if (!key)
		return (MEMORY_ERROR_PT);
	ft_strlcpy(key, line, (size + 1));
	return (key);
}
