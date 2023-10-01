
#include "minishell.h"
#include "minishell_louis.h"


void	wait_childs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_command)
	{
		if (data->cmd[i]->pid != -1)
			waitpid(data->cmd[i]->pid, 0, 0);
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

int	ft_envlstsize(t_envlist *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*join_lign_env(t_envlist *list)
{
	size_t		i;
	size_t		j;
	char	*ret;

	ret = malloc(sizeof(char) * ft_strlen(list->key) + ft_strlen(list->val) + 2);
	i = 0;
	j = 0;
	while (i < ft_strlen(list->key))
	{
		ret[i] = list->key[i];
		i++;
	}
	ret[i] = '=';
	i++;
	while (j < ft_strlen(list->val))
	{
		ret[i + j] = list->val[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	**list_to_array(t_envlist *list)
{
	int	i;
	int j;
	char **ret;

	i = ft_envlstsize(list);
	ret = ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	j = 0;
	while(j < i)
	{
		ret[j] = join_lign_env(list);
		list = list->next;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

int	child_process(t_data *data, t_pipe *pipes)
{
	char	*exec;
	char	*path_temp;
	t_cmd	*cmd;
	char	**envp;

	envp = list_to_array(data->envp);
	cmd = data->cmd[data->current_cmd];
	pipes = handle_redirection(data, pipes);
	if (cmd->cmd_type != no)
	{
		handle_builtins(data);
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
		data->exec_val = -1;
		//recup la vraie val (ernno) ?
		return (data->exec_val);
	}
	//ft_display_tab_cmd(*data);
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	execve(exec, cmd->cmd_args, envp);
	data->exec_val = -1;
	//recup la vraie val (ernno) ?
	return (data->exec_val);
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

t_pipe	*gen_child(t_data *data, t_pipe *pipes)
{
	pid_t	pid;

	if (data->nb_command > 1)
	{
		if (data->current_cmd == 0)
		{
			if (pipe(pipes->tube[1]) != 0)
				error_pipe();
				//error(free_data)
		}
		else
			pipes = new_pipes(pipes, data->current_cmd);	
	}
	if (data->cmd[data->current_cmd]->cmd_type != no && data->nb_command == 1)
	{
		pipes = handle_redirection(data, pipes);
		handle_builtins(data);
		return (pipes);
	}
	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
		data->exec_val = child_process(data, pipes);
	data->cmd[data->current_cmd]->pid = pid;
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
	t_pipe	*pipe;
	int		temp_stdin;
	int		temp_stdout;

	temp_stdin = dup(0);
	temp_stdout = dup(1);
	data->current_cmd = 0;
	if (data->nb_command > 1)
	{
		pipe = malloc(sizeof(t_pipe));
		if (!pipe)
			error_malloc();
	}
	while (data->current_cmd < data->nb_command)
	{
		pipe = gen_child(data, pipe);
		data->current_cmd++;
	}
	if (data->nb_command > 1)
		close_pipes(pipe);
	wait_childs(data);
	close_list_args(data->cmd, data->nb_command, temp_stdin, temp_stdout);
	//free_list_args(data->cmd, pipe, data->nb_command);
	return (0);
}
