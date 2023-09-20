/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:13:20 by madavid           #+#    #+#             */
/*   Updated: 2023/09/20 20:13:31 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error(int err_code)
{
	if (err_code == MEMORY_ERROR_NB)
		ft_dprintf(STDERR_FILENO, "Problem with memory allocation\n");
	return (0);
}

