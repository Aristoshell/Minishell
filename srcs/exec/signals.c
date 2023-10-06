/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 22:15:18 by lmarchai          #+#    #+#             */
/*   Updated: 2023/10/06 21:45:12 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	sighandler_heredoc(int sig)
{
    (void)sig;
    //fixe la valeur $? a 130
    //retourne au prompt
    printf("\n");
    glb = 130;
    return ;
}

void    handle_signals_heredoc()
{
    signal(SIGINT, &sighandler_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
