/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:07 by lmarchai          #+#    #+#             */
/*   Updated: 2023/07/11 18:25:55 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	error_dup2(void)
{
	printf("error dup2");
}

void	error_pipe(void)
{
	printf("error pipe");
}

void	handle_file_redirection(t_cmd **cmd)
{
	if((*cmd)->input == file_)
	{
		if((*cmd)->fd_in != -1)
			if (dup2((*cmd)->fd_in, 0) == -1)
				error_dup2();
	}
	if((*cmd)->input == file_)
	{
		if((*cmd)->fd_out != -1)
			if (dup2((*cmd)->fd_out, 1) == -1)
				error_dup2();
	}
}

void	handle_pipe_redirection(t_cmd **cmd)
{
	int tube[2];

	if ((*cmd)->input == pipe_)
	{
		if((*cmd)->fd_in != -1)
		{
			if (dup2((*cmd)->fd_in, 0) == -1)
				error_dup2();
		}
	}
	if ((*cmd)->output == pipe_ && (*cmd)->next != NULL && 
		(*cmd)->next->input == pipe_)
	{
		if (pipe(&tube[2]) == -1)
			error_pipe();
		(*cmd)->fd_out = tube[0];
		(*cmd)->next->fd_in = tube[1];
		if((*cmd)->fd_out != -1)
		{
			if (dup2((*cmd)->fd_out, 0) == -1)
				error_dup2();
		}
	}
}

void    handle_redirections(t_cmd **cmd)
{
	if ((*cmd)->input == file_ || (*cmd)->output == file_)
		handle_file_redirection(cmd);
	if ((*cmd)->input == pipe_ || (*cmd)->output == pipe_)
		handle_pipe_redirection(cmd);
	//if ((*cmd)->input == heredoc_)
		//handle_heredoc_redirection(cmd);
	//if ((*cmd)->output == append_)
		//handle_append_redirection(cmd);
}

void    child_process(t_cmd **cmd, char **envp)
{
    char *command;
    char *paths;

    handle_redirections(cmd);
    paths = find_path(envp);
    (*cmd)->path_cmd = ft_split(paths, ':');
    command = get_cmd((*cmd)->path_cmd, (*cmd)->cmd_args[0]);
    if(!command)
    {
        printf("cmd error\n");
        exit(1);
    }
    execve(command, (*cmd)->cmd_args, envp);
}