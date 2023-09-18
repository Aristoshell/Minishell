/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:07 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 09:29:38 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void error_dup2(void)
{
	printf("error dup2");
}

void error_pipe(void)
{
	printf("error pipe");
}

void wait_childs(t_cmd *cmd[4])
{
	int i;
	
	i = 0;
	while(cmd[i])
	{
		waitpid(cmd[i]->pid, 0, 0);
		i++;
	}
}

void	close_pipes(t_pipe *pipes)
{
	close(pipes->tube[0][0]);
	close(pipes->tube[0][1]);
	close(pipes->tube[1][0]);
	close(pipes->tube[1][1]);
}

int strlen_list(t_cmd *cmd[4])
{
	int i;

	i = 0;
	while(cmd[i])
		i++;
	return (i);
}

t_pipe	*handle_redirection(t_cmd *cmd, t_pipe *pipes)
{
	if (cmd->input == pipe_ || cmd->output == pipe_)
	{
		if(cmd->input == pipe_ && cmd->output != pipe_)
		{
			if (dup2(pipes->tube[0][0], 0) == - 1 || dup2(cmd->fd_out, 1) == -1)
				error_dup2();
			close(pipes->tube[0][1]);
			return(pipes);
		}
		
		if(cmd->input != pipe_ && cmd->output == pipe_)
		{
			if (dup2(pipes->tube[1][1], 1) == - 1 || dup2(cmd->fd_in, 0) == -1)
				error_dup2();
			close(pipes->tube[1][0]);
			return(pipes);
		}
		if (dup2(pipes->tube[0][0], 0) == - 1 || dup2(pipes->tube[1][1], 1) == -1)
			error_dup2();
		close (pipes->tube[0][1]);
		close (pipes->tube[1][0]);
		return(pipes);
	}
	else
	{
		if (dup2(cmd->fd_in, 0) == - 1 || dup2(cmd->fd_out, 1) == -1)
			error_dup2();
		close (pipes->tube[0][1]);
		close (pipes->tube[1][0]);
	}
	return(pipes);
}

void	handle_builtin(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	if (!envp || !pipes)
		return ;
	if (cmd->cmd_type == cmd_echo)
		printf("builtin echo");
	if (cmd->cmd_type == cmd_echo_n)
		printf("builtin echo_n");
	if (cmd->cmd_type == cmd_cd)
		printf("builtin cd");
	if (cmd->cmd_type == cmd_pwd)
		printf("builtin pwd");
	if (cmd->cmd_type == cmd_export)
		printf("builtin export");
	if (cmd->cmd_type == cmd_unset)
		printf("builtin unset");
	if (cmd->cmd_type == cmd_env)
		printf("builtin env");
	if (cmd->cmd_type == cmd_exit)
		printf("builtin exit");
}


/*
childs classique 
- Le Paths de chaque fonction est recuperer dans celui ci afin de prevoir les probleme 
au cas ou un unset soit realiser avant ou entre deux commande
*/

void	child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	pipes = handle_redirection(cmd, pipes);
	if(cmd->cmd_type != no)
		handle_builtin(cmd, pipes, envp);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	if(!cmd->cmd_args)
		return ;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	execve(exec, cmd->cmd_args, envp);
}

/*
fonction new pipe qui sert a realiser l'etape explique dans le commentaire ci dessous
*/

t_pipe *new_pipes(t_pipe *pipes, int i)
{
	if (i != 1)
	{
		close(pipes->tube[0][0]);
		close(pipes->tube[0][1]);
	}
	pipes->tube[0][0] = pipes->tube[1][0];
	pipes->tube[0][1] = pipes->tube[1][1];
	if (pipe(pipes->tube[1]) !=0 )
		error_pipe();
	return (pipes);
}

/*
c'est dans ces fonctions que l'on vas 
- faire nos fork
- creer les pipes
- appeller les childs
*/

t_pipe	*gen_child(t_cmd *cmd, t_pipe *pipes, char **envp, int i)
{
	pid_t pid;
	
	if (i == 0)
	{
		if (pipe(pipes->tube[1]) != 0)
			error_pipe();
	}
	else
		pipes = new_pipes(pipes, i);
	pid = fork();
	if (pid == 0)
		child_process(cmd, pipes, envp);
	cmd->pid = pid;
	return(pipes);
}

/*
ici et pour le dernier child on vas appeller la fonction 
new pipe vas decaller les pipes dans notre tableau a double entre

Exemple 1 cas du premier mid child :
(c'est un cas specifique car pour le first child on a besoin que d'un seul pipe)

les fd sont initialiser a -2 ce qui ne pourras pas etre le cas plus tard 
	car cela creer une erreur valgrind
avant appel de la fonction new_pipe :

[0][0] --> -2
[0][1] --> -2
[1][0] -->  5
[1][1] -->  6

On voit que les fd du tube [0] sont encore a leur valeur d'initialisation
tandis que les fd du tube [1] sont eux a des valeurs reel car on les a utilises
dans le first child

apres appel :
[0][0] --> 5
[0][1] --> 6
[1][0] --> 7
[1][1] --> 8

les valeurs qui etaient dans le fd du tube[1] sont passe dans le tube [0]
et le tube [1] s'est vu attribue de nouveau fd

--------------------------------------------------------------------------

Exemple 2 cas de tout les autres mid child

avant appel de la fonction new_pipe :

[0][0] --> 5
[0][1] --> 6
[1][0] --> 7
[1][1] --> 8

apres appel :

[0][0] --> 7
[0][1] --> 8
[1][0] --> 9
[1][1] --> 10
*/


/*
fonction principale qui permet de parcourir la liste que tu m'envoies
ma partie commence vraiment ici

- premiere case du tableau on appelle la fonction gen_first_child
- toutes les cases sauf la derniere on appelle gen_mid_child
- pour la derniere on appelle gen_last_child
on close les pipes
et on attends que les childs aient fini d'executer
*/

void	free_list_args(t_cmd *cmd[4], t_pipe *pipes, int len_list)
{
	int	i;
	int	j;

	i = 0;
	while (i < len_list)
	{
		j = 0;
		while(cmd[i]->cmd_args[j])
		{
			free(cmd[i]->cmd_args[j]);
			j++;
		}
		free(cmd[i]->cmd_args);
		free(cmd[i]);
		i++;
	}
	free(pipes);
}


void	cross_array_list(t_cmd *cmd[4], char **envp)
{
	int 	i;
	int 	len_list;
	t_pipe 	*pipe;

	if (!envp)
		return;
	i = 0;
	pipe = malloc(sizeof(t_pipe));
	len_list = strlen_list(cmd);
	while(i < len_list)
	{
		pipe = gen_child(cmd[i], pipe, envp, i);
		i++;
	}
	close_pipes(pipe);
	wait_childs(cmd);
	free_list_args(cmd, pipe, len_list);
	return;
}