/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 09:49:06 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/29 16:44:19 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"


void	wait_childs(t_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i]->pid != -1)
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

int	child_process(t_cmd **tab_cmd, t_pipe *pipes, char **envp, int i)
{
	char	*exec;
	char	*path_temp;
	t_cmd	*cmd;
	int		status;

	cmd = tab_cmd[i];
	pipes = handle_redirection(cmd, pipes);
	if (cmd->cmd_type != no)
	{
		handle_builtins(tab_cmd, envp, i);
		exit(0);
	}
	path_temp = find_path(envp);
	if (path_temp)
		cmd->path_cmd = ft_split(path_temp, ':');
	else
		cmd->path_cmd = NULL;
	if (!cmd->cmd_args)
	{
		//si la commande est mauvais il faut free et close
		status = -1;
		//recup la vraie val (ernno) ?
		return (status);
	}
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	execve(exec, cmd->cmd_args, envp);
	status = -1;
	//recup la vraie val (ernno) ?
	return (status);
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

t_pipe	*new_pipes(t_pipe *pipes, int i)
{
	if (i != 1)
	{
		close(pipes->tube[0][0]);
		close(pipes->tube[0][1]);
	}
	pipes->tube[0][0] = pipes->tube[1][0];
	pipes->tube[0][1] = pipes->tube[1][1];
	if (pipe(pipes->tube[1]) != 0)
		error_pipe();
	return (pipes);
}

/*
fonction gen_child qui vas modifier les fds dans les pipes puis fork 
et enfin appeler la fonction child process
*/

t_pipe	*gen_child(t_cmd **cmd, t_pipe *pipes, char **envp, int i, int *status)
{
	pid_t	pid;
	int		len_list;

	len_list = strlen_list(cmd);
	/*if (len_list == -1)
		error(free_data)*/
	if (len_list > 1)
	{
		if (i == 0)
		{
			if (pipe(pipes->tube[1]) != 0)
				error_pipe();
				//error(free_data)
		}
		else
			pipes = new_pipes(pipes, i);	
	}
	if (cmd[i]->cmd_type != no && len_list == 1)
	{
		pipes = handle_redirection(cmd[i], pipes);
		handle_builtins(cmd, envp, i);
		return (pipes);
	}
	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
		*status = child_process(cmd, pipes, envp, i);
	cmd[i]->pid = pid;
	return (pipes);
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

int	cross_array_list(t_data *data)
{
	int		i; //data->current_cmd
	int		len_list; //data->nb_cmd
	int		status; //data->exec_val
	t_pipe	*pipe;

	i = 0;
	status = 0;
	len_list = strlen_list(cmd);
	if (len_list > 1)
	{
		pipe = malloc(sizeof(t_pipe));
		if (!pipe)
			error_malloc();
	}
	while (i < len_list)
	{
		pipe = gen_child(cmd, pipe, envp, i, &status);
		i++;
	}
	if (len_list > 1)
	{
		close_pipes(pipe);
		wait_childs(cmd);
	}
	close_list_args(cmd, len_list);
	free_list_args(cmd, pipe, len_list);
	return ;
}
