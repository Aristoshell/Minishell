
#include "minishell.h"
#include "minishell_louis.h"

int g_glb = 0;

void	wait_childs(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_command)
	{
		if (data->cmd[i]->pid != -1)
			waitpid(data->cmd[i]->pid, &status, 0);
		if (data->nb_command > 1 || data->cmd[i]->cmd_type == no)
			data->exec_val = WEXITSTATUS(status);
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
		if (lst->flag == MASK_ENV)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	*join_lign_env(t_envlist *list)
{
	size_t		i;
	size_t		j;
	char		*ret;

	ret = malloc(sizeof(char) * ft_strlen(list->key) \
		+ ft_strlen(list->val) + 2);
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
	while (j < i)
	{
		if (list->flag == MASK_ENV)
		{
			ret[j] = join_lign_env(list);
			j++;
		}
		list = list->next;
	}
	ret[j] = NULL;
	return (ret);
}

void free_envp(char **a)
{
	int i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

int	child_process(t_data *data, t_pipe *pipes)
{
	char	*exec;
	char	*path_temp;
	t_cmd	*cmd;
	char	**envp;
	int		exec_val;
	
	close(data->stdin_save);
	close(data->stdout_save);
	envp = list_to_array(data->envp);
	cmd = data->cmd[data->current_cmd];
	pipes = handle_redirection(data, pipes);
	handle_signals_exec(data);
	if (g_glb == 999)
	{
		close_files(data);
		close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
		close_pipes(data, pipes);
		ft_clean_t_data(data);
		free_envp(envp);
		exit (1);
	}
	close_files(data);
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	if (cmd->cmd_type != no)
	{
		exec_val = handle_builtins(data, pipes);
		free_envp(envp);
		close_pipes(data, pipes);
		ft_clean_t_data(data);
		exit(exec_val);
	}
	path_temp = find_path(envp);
	if (path_temp)
	{
		cmd->path_cmd = ft_split(path_temp, ':');
		if (!cmd->path_cmd)
		{
			exec_val = data->exec_val;
			handle_builtins(data, pipes);
			free_envp(envp);
			close_pipes(data, pipes);
			ft_clean_t_data(data);
			exit(2);
		}
	}
	else
		cmd->path_cmd = NULL;
	exec = get_cmd(cmd->path_cmd, cmd->cmd_args[0]);
	if (!exec || cmd->cmd_type == no_cmd)
	{
		free_envp(envp);
		close_pipes(data, pipes);
		close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
		close_files(data);
		if (data->exec_val != 130)
			exec_val = g_glb;
		else
			exec_val = 130;
		ft_clean_t_data(data);
		exit(exec_val);
	}
	execve(exec, cmd->cmd_args, envp);
	free_envp(envp);
	close_pipes(data, pipes);
	if (data->exec_val != 130)
		exec_val = g_glb;
	else
		exec_val = 130;
	ft_clean_t_data(data);
	ft_dprintf(STDERR_FILENO, "ON EST PAS DANS UNE FUSEE C'EST OK\n");
	exit(127);
}

/*
new pipe vas decaller les pipes dans notre tableau a double entre

Exemple 1 cas du premier mid child :
(c'est un cas specifique car pour le first child on a besoin que d'un seul pipe)

les fd sont initialiser a -2
avant appel de la fonction new_pipe :
envp = list_to_array(data->envp);
	cmd = data->cmd[data->current_cmd];ore a leur valeur d'initialisation
tandis que les fd du tube [1] sont eux a des valeurs reel car on les a utilises
dans le first child
fd_in
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
	if (i > 1)
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

	handle_heredoc(data);
	if (data->nb_command > 1 && data->current_cmd >= 1)
		pipes = new_pipes(pipes, data->current_cmd);
	if (data->cmd[data->current_cmd]->cmd_type != no && data->cmd[data->current_cmd]->cmd_type != no_cmd 
		&& data->nb_command == 1)
	{
		pipes = handle_redirection(data, pipes);
		if (g_glb == 999)
			return (data->exec_val = 1, pipes);
		data->exec_val = handle_builtins(data, pipes);
		return (pipes);
	}
	pid = fork();
	if (pid == -1)
		error_fork();
	if (pid == 0)
		child_process(data, pipes);
	else
		data->cmd[data->current_cmd]->pid = pid;
	return (pipes);
}

/*
ma partie commence vraiment ici (fonction que tu appelera)
cmd est un t_cmd** (pour les tests je me suis limite a 3 commandes)
il faudras quil se termine par un /0

declaration des deux pipes qu2
1
attente des childs
free tout
*/

void	unlink_files(t_list *l)
{
	t_files	*f;

	if (!l)
		return ;
	f = (t_files *)l->content;
	while (l)
	{
		if (f->filetype == heredoc_)
			unlink(f->filename);
		l = l->next;
		if (l)
			f = (t_files *)l->content;
	}
}

void	close_files(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_command)
	{
		if (data->cmd[i]->input == file_from && data->cmd[i]->fd_in != -1 && data->cmd[i]->fd_in != -2)
			close(data->cmd[i]->fd_in);
		if (data->cmd[i]->output == file_to && data->cmd[i]->fd_out != -1 && data->cmd[i]->fd_out != -2)
			close(data->cmd[i]->fd_out);
		unlink_files(data->cmd[i]->list_files);
		i++;
	}
}

int	cross_array_list(t_data *data)
{
	t_pipe	*pipe_;

	data->stdin_save = dup(0);
	data->stdout_save = dup(1);
	pipe_ = NULL;
	data->current_cmd = 0;
	if (data->nb_command > 1)
	{
		pipe_ = malloc(sizeof(t_pipe));
		pipe_->tube[0][0] = -1;
		pipe_->tube[0][1] = -1;
		pipe_->tube[1][1] = -1;
		pipe_->tube[1][1] = -1;
		if (!pipe_)
			return (close_and_free(NULL, data->stdin_save, data->stdout_save, 0), MEMORY_ERR_NB);
		if (pipe(pipe_->tube[1]) != 0)
			return (close_and_free(pipe_, data->stdin_save, data->stdout_save, 1), MEMORY_ERR_NB);
	}
	while (data->current_cmd < data->nb_command)
	{
		pipe_ = gen_child(data, pipe_);
		if (pipe_ == NULL && data->nb_command > 1)
			return (0);
		data->current_cmd++;
	}
	close_pipes(data, pipe_);
	wait_childs(data);
	if (g_glb == 130)
		data->exec_val = 130;
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_files(data);
	return (0);
}
