/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:36:51 by lmarchai          #+#    #+#             */
/*   Updated: 2023/07/11 18:35:38 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	error_fork(void)
{
	printf("error_fork");
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->next = malloc(sizeof(t_cmd));
	if (!cmd)
		return (-1);

	//first command
	cmd->cmd_args = gen_first_cmd(argv);
	cmd->cmd_type = no;
	cmd->input = file_;
	cmd->output = pipe_;
	cmd->fd_in = open("in", O_RDONLY);
	cmd->fd_out = -2;
	//second command
	cmd->next->cmd_args = gen_sec_cmd(argv, argc);
	cmd->cmd_type = no;
	cmd->next->input = pipe_;
	cmd->next->input = file_;
	cmd->fd_in = -2;
	cmd->next->fd_out = open("out", O_CREAT | O_TRUNC | O_RDWR, 0777);
	cmd->next->next = NULL;
	// for(int i = 0; cmd->cmd_args[i]; i++)
		// printf("%s ", cmd->cmd_args[i]);
	// printf("\n");
	// for(int i = 0; cmd->next->cmd_args[i]; i++)
		// printf("%s ", cmd->next->cmd_args[i]);
	// printf("\n");
	cmd->pid = fork();
	if (cmd->pid == -1)
		error_fork();
	if (cmd->pid == 0)
		child_process(&cmd, envp);
	if (cmd->next->pid == -1)
		error_fork();
	if (cmd->next->pid == 0)
		child_process(&cmd, envp);
	waitpid(cmd->pid, 0, 0);
	waitpid(cmd->next->pid, 0, 0);
	return (0);
}
