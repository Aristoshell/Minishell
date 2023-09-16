/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:36:51 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/16 14:32:35 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	error_fork(void)
{
	printf("error_fork");
	exit(1);
}

/*
creation des arguments des listes qu'on vas utiliser
*/

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd[4];
	
	if (!argv || !argc || !envp)
		printf("no arg");

	cmd[0] = malloc(sizeof(t_cmd));
	cmd[1] = malloc(sizeof(t_cmd));
	cmd[2] = malloc(sizeof(t_cmd));
	cmd[3] = NULL;
	
	cmd[0]->pid = -1;
	cmd[0]->cmd_args = gen_first_cmd(argv);
	cmd[0]->cmd_type = no;
	cmd[0]->input = file_;
	cmd[0]->output = pipe_;
	cmd[0]->heredoc_name = NULL;
	cmd[0]->heredoc_sep = NULL;
	cmd[0]->fd_in = open("in", O_RDONLY);
	cmd[0]->fd_out = -2;
	
	
	cmd[1]->pid = -1;
	cmd[1]->cmd_args = gen_sec_cmd(argv);
	cmd[1]->cmd_type = no;
	cmd[1]->input = file_;
	cmd[1]->output = pipe_;
	cmd[1]->heredoc_name = NULL;
	cmd[1]->heredoc_sep = NULL;
	cmd[1]->fd_in = -2;
	cmd[1]->fd_out = -2;
	

	cmd[2]->pid = -1;
	cmd[2]->cmd_args = gen_third_cmd(argv,argc);
	cmd[2]->cmd_type = no;
	cmd[2]->input = file_;
	cmd[2]->output = pipe_;
	cmd[2]->heredoc_name = NULL;
	cmd[2]->heredoc_sep = NULL;
	cmd[2]->fd_in = -2;
	cmd[2]->fd_out = open("out", O_CREAT | O_TRUNC | O_RDWR, 0777);

	cross_array_list(cmd, envp);
	return (0);
}
