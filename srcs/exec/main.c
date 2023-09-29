/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:36:51 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/29 15:57:48 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"


/*
creation des arguments des listes qu'on vas utiliser
*/

static void    sighandler_heredoc(int signum)
{
	if (!signum)
	printf("\n");
	exit(0);
}

void	heredoc_signals_test()
{
	char buf[1];
	signal(SIGINT, &sighandler_heredoc); //CTRL + d
    signal(SIGQUIT, SIG_IGN);			//CTRL + \*/
	while (buf[0] != '\n')
	{
		if (read(0, buf, 1) == 0 || read(0, buf, 1) == 0)
		{
			printf("oui\n");			//CTRL + d
			exit(0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	**cmd;

	//heredoc_signals_test();
	int i = 0;
	if (!argv || !argc || !envp)
		printf("no arg");
	
	if (!ft_isnumber(argv[1]))
	{
		printf("first arg must be the number of cmd you'll pass to the exec (3 max)");
		return (1);
	}
	if (ft_atoi(argv[1]) > 3)
	{
		printf("maximum cmd you can pass to the exec is 3");
		return (1);
	}
	cmd = malloc(sizeof(t_cmd) * ft_atoi(argv[1]) + 1);
	while(i < ft_atoi(argv[1]))
	{
		cmd[i] = malloc(sizeof(t_cmd));
		i++;
	}
	cmd[i] = NULL;
	if (ft_atoi(argv[1]) == 1)
	{
		cmd[0]->pid = -1;
		cmd[0]->cmd_args = gen_first_cmd(argv);
		cmd[0]->cmd_type = no;
		cmd[0]->input = file_;
		cmd[0]->output = file_;
		cmd[0]->heredoc_name = NULL;
		cmd[0]->heredoc_sep = NULL;
		cmd[0]->fd_in = 0;
		cmd[0]->fd_out = 1;
	}
	else if (ft_atoi(argv[1]) == 2)
	{
		cmd[0]->pid = -1;
		cmd[0]->cmd_args = gen_first_cmd(argv);
		cmd[0]->cmd_type = cmd_pwd;
		cmd[0]->input = file_;
		cmd[0]->output = pipe_;
		cmd[0]->heredoc_name = NULL;
		cmd[0]->heredoc_sep = NULL;
		cmd[0]->fd_in = 0;
		cmd[0]->fd_out = -2;
		
		cmd[1]->pid = -1;
		cmd[1]->cmd_args = gen_sec_cmd(argv);
		cmd[1]->cmd_type = no;
		cmd[1]->input = pipe_;
		cmd[1]->output = file_;
		cmd[1]->heredoc_name = NULL;
		cmd[1]->heredoc_sep = NULL;
		cmd[1]->fd_in = -2;
		cmd[1]->fd_out = 1;
	}
	else if ( ft_atoi(argv[1]) == 3)
	{
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
		cmd[1]->input = pipe_;
		cmd[1]->output = pipe_;
		cmd[1]->heredoc_name = NULL;
		cmd[1]->heredoc_sep = NULL;
		cmd[1]->fd_in = -2;
		cmd[1]->fd_out = -2;
		
		cmd[2]->pid = -1;
		cmd[2]->cmd_args = gen_third_cmd(argv,argc);
		cmd[2]->cmd_type = no;
		cmd[2]->input = pipe_;
		cmd[2]->output = file_;
		cmd[2]->heredoc_name = NULL;
		cmd[2]->heredoc_sep = NULL;
		cmd[2]->fd_in = -2;
		cmd[2]->fd_out = open("out", O_CREAT | O_TRUNC | O_RDWR, 0777);
	}
	cross_array_list(cmd, envp);
	return (1);
}
