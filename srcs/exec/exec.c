
#include "minishell.h"
#include "minishell_louis.h"

int g_glb = 0;

/*
ma partie commence vraiment ici (fonction que tu appelera)
cmd est un t_cmd** (pour les tests je me suis limite a 3 commandes)
il faudras quil se termine par un /0

declaration des deux pipes qu2
1
attente des childs
free tout
*/

void	init_pipe_tube()
{
	data->pipe->tube[0][0] = -1;
	data->pipe->tube[0][1] = -1;
	data->pipe->tube[1][1] = -1;
	data->pipe->tube[1][1] = -1;
}

int	cross_array_list(t_data *data)
{
	data->stdin_save = dup(0); // verif
	data->stdout_save = dup(1); // verif
	data->current_cmd = 0;
	if (data->nb_command > 1)
	{
		data->pipe = malloc(sizeof(t_pipe));
		if (!data->pipe)
			return (close_and_free(NULL, data->stdin_save, data->stdout_save, 0), MEMORY_ERR_NB);
		init_pipe_tube();
		if (pipe(data->pipe->tube[1]) != 0)
			return (free(data->pipe), close_and_free(pipe_, data->stdin_save, data->stdout_save, 1), MEMORY_ERR_NB);
	}
	while (data->current_cmd < data->nb_command)
	{
		data->pipe = gen_child(data, data->pipe);
		if (data->pipe == NULL && data->nb_command > 1)
			return (0); //wtf
		data->current_cmd++;
	}
	close_pipes(data, data->pipe);
	wait_childs(data);
	if (g_glb == 130)
		data->exec_val = 130;
	close_fd(data->cmd, data->nb_command, data->stdin_save, data->stdout_save);
	close_files(data);
	return (0);
}
