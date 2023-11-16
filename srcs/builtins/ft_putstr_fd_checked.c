/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_checked.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:56:11 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/16 14:44:51 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_putstr_fd_checked(char *s, int fd)
{
	if (s == NULL)
		return (1);
	if (write(fd, s, ft_strlen(s)) != (ssize_t)ft_strlen(s))
	{
		ft_dprintf(2, "minishell: echo: write error:");
		ft_dprintf(2, " No space left on device\n");
		return (1);
	}
	return (0);
}
