/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:40:07 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/16 14:50:27 by lmarchai         ###   ########.fr       */
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

/*
childs classique 
- Le Paths de chaque fonction est recuperer dans celui ci afin de prevoir les probleme 
au cas ou un unset soit realiser avant ou entre deux commande
*/

void	first_child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	if (dup2(pipes->tube[1][1], 1) == - 1
		|| dup2(cmd->fd_in, 0) == -1)
		error_dup2();
	close(pipes->tube[1][0]);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if(!cmd->cmd_args)
		return ;
	execve(exec, cmd->cmd_args, envp);[0][0] --> 5
[0][1] --> 6
[1][0] --> 7
[1][1] --> 8
}

void	mid_child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	if (dup2(pipes->tube[0][0], 0) == - 1
		|| dup2(pipes->tube[1][1], 1) == -1)
		error_dup2();
	close (pipes->tube[0][1]);
	close (pipes->tube[1][0]);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if(!cmd->cmd_args)
		return ;
	execve(exec, cmd->cmd_args, envp);
}

void	last_child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	if (dup2(pipes->tube[0][0], 0) == - 1
		|| dup2(cmd->fd_out, 1) == -1)
		error_dup2();
	close(pipes->tube[0][1]);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if(!cmd->cmd_args)
		return ;
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

t_pipe	*gen_first_child(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	pid_t pid;
	
	if (pipe(pipes->tube[1]) != 0)
		error_pipe();
	pid = fork();
	if (pid == 0)
		first_child_process(cmd, pipes, envp);
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

t_pipe	*gen_mid_child(t_cmd *cmd, t_pipe *pipes, char **envp, int i)
{
	pid_t	pid;
	
	new_pipes(pipes, i);
	pid = fork();
	if (pid == 0)
		mid_child_process(cmd, pipes, envp);
	cmd->pid = pid;
	return(pipes);
}

t_pipe	*gen_last_child(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	pid_t pid;
	
	new_pipes(pipes, 0);
	pid = fork();
	if (pid == 0)
		last_child_process(cmd, pipes, envp);
	cmd->pid = pid;
	return(pipes);
}


/*
fonction principale qui permet de parcourir la liste que tu m'envoies
ma partie commence vraiment ici

- premiere case du tableau on appelle la fonction gen_first_child
- toutes les cases sauf la derniere on appelle gen_mid_child
- pour la derniere on appelle gen_last_child
on close les pipes
et on attends que les childs aient fini d'executer
*/

void	cross_array_list(t_cmd *cmd[4], char **envp)
{
	int 	i;
	int 	len_list;
	t_pipe 	*pipe;

	if (!envp)
		return;
	i = 1;
	pipe = malloc(sizeof(t_pipe));
	len_list = strlen_list(cmd);
	pipe = gen_first_child(cmd[0], pipe, envp);
	while(i < len_list - 1)
	{
		pipe = gen_mid_child(cmd[i], pipe, envp, i);
		i++;
	}
	pipe = gen_last_child(cmd[i], pipe, envp);
	close_pipes(pipe);
	wait_childs(cmd);
	return;
}