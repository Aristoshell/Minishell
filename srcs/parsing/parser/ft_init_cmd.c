
#include "minishell.h"
#include "minishell_louis.h"

int	ft_init_cmd(t_data *data, int i)
{
	data->cmd[i] = malloc(sizeof(t_cmd));
	if(!data->cmd[i])
		return (MEMORY_ERROR_NB); // attention check retour de cette fonction avant (previously on retournais -1) + effacer ce qui a ete alloue avant
	data->cmd[i]->pid = -1;
	data->cmd[i]->cmd_args = NULL;
	data->cmd[i]->cmd_type = no;
	data->cmd[i]->path_cmd = NULL;
	data->cmd[i]->input = stdin_;
	data->cmd[i]->output = stdout_;
	data->cmd[i]->fd_in = -1;
	data->cmd[i]->fd_out = -1;
	return (FUNCTION_SUCCESS);
}
