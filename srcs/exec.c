/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:49:06 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 10:56:48 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

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

/*
process du child une fois fork
on appel handle redirections (redir.c) qui s'occupe de dup2 l'entree et la sortie
puis handle builtins (set_up_cmd.c) dans le cas ou on a un builtin
on recup la variable d'env PATH que l'on vas split en fonction du char :
on execute ensuite la commande voulue (sauf builtins)
*/

void	child_process(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	char	*exec;
	char	*path_temp;
	
	pipes = handle_redirection(cmd, pipes);
	if(cmd->cmd_type != no)
		handle_builtins(cmd, pipes, envp);
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	if(!cmd->cmd_args)
	{
		//si la commande est mauvais il faut free et close
		return ;
	}
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	execve(exec, cmd->cmd_args, envp);
	//si execve fail il faut free et close
}

/*
new pipe vas decaller les pipes dans notre tableau a double entre

Exemple 1 cas du premier mid child :
(c'est un cas specifique car pour le first child on a besoin que d'un seul pipe)

les fd sont initialiser a -2
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
fonction gen_child qui vas modifier les fds dans les pipes puis fork 
et enfin appeler la fonction child process
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
	if (pid == -1)
		error_fork();
	if (pid == 0)
		child_process(cmd, pipes, envp);
	cmd->pid = pid;
	return(pipes);
}

/*
ma partie commence vraiment ici (fonction que tu appelera)
cmd est un t_cmd** (pour les tests je me suis limite a 3 commandes)
il faudras quil se termine par un /0

declaration des deux pipes qui nous serviront ensuite
on parcours le tableau de liste et on apelle la fonction gen child
close les pipes
attente des childs
free tout
*/

void	cross_array_list(t_cmd *cmd[4], char **envp)
{
	int 	i;
	int 	len_list;
	t_pipe 	*pipe;

	i = 0;
	pipe = malloc(sizeof(t_pipe));
	if (!pipe)
		error_malloc();
	len_list = strlen_list(cmd);
	while(i < len_list)
	{
		pipe = gen_child(cmd[i], pipe, envp, i);
		i++;
	}
	close_pipes(pipe);
	wait_childs(cmd);
	close_list_args(cmd, len_list);
	free_list_args(cmd, pipe, len_list);
	return;
}