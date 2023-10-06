/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/06 11:34:53 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	sighandler_heredoc()
{
    //fixe la valeur $? a 130
	//retourne au prompt
    exit(130);
}

__sighandler_t	handle_signals_heredoc(void)
{
    return(signal(SIGINT, &sighandler_heredoc));
    return(signal(SIGQUIT, SIG_IGN));
}
