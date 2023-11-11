
#include "minishell.h"
#include "minishell_louis.h"

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

void	exit_err_redir(t_data *data, char **envp)
{
	close_files(data);
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_pipes(data, data->pipe);
	ft_clean_t_data(data);
	free_envp(envp);
	exit (1);
}

void	exit_builtins(t_data *data, char **envp)
{
	int		exec_val;

	exec_val = handle_builtins(data, data->pipe);
	free_envp(envp);
	close_pipes(data, data->pipe);
	ft_clean_t_data(data);
	exit(exec_val);
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
	envp = list_to_array(data->envp); // verif
	cmd = data->cmd[data->current_cmd];
	pipes = handle_redirection(data, pipes);
	handle_signals_exec();
	if (g_glb == ERROR_REDIR)
		exit_err_redir(data, envp);
	close_files(data);
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	if (cmd->cmd_type != no)
		exit_builtins(data, envp);
	path_temp = find_path(envp);
	if (path_temp)
	{
		cmd->path_cmd = ft_split(path_temp, ':'); // verif
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
fonction gen_child qui vas modifier les fds dans les pipes puis fork 
et enfin appeler la fonction child process
*/

t_pipe	*gen_child(t_data *data, t_pipe *pipes)
{
	pid_t	pid;

	handle_heredoc(data);
	if (data->nb_command > 1 && data->current_cmd >= 1)
		pipes = new_pipes(pipes, data->current_cmd);
	if (data->cmd[data->current_cmd]->cmd_type != no
		&& data->cmd[data->current_cmd]->cmd_type != no_cmd 
		&& data->nb_command == 1)
	{
		pipes = handle_redirection(data, pipes);
		if (g_glb == ERROR_REDIR)
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
