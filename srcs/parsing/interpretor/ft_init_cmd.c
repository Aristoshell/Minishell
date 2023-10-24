#include "minishell.h"
#include "minishell_louis.h"

int	ft_init_cmd(t_data *data, int i)
{
	data->cmd[i] = malloc(sizeof(t_cmd));
	if (!data->cmd[i])
		return (MEMORY_ERR_NB);
	data->cmd[i]->pid = -1;
	data->cmd[i]->cmd_args = NULL;
	data->cmd[i]->cmd_type = no;
	data->cmd[i]->path_cmd = NULL;
	data->cmd[i]->list_files = NULL;
	data->cmd[i]->fd_in = 0;
	data->cmd[i]->fd_out = 1;
	data->cmd[i]->input = stdin_;
	data->cmd[i]->output = stdout_;
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd(t_cmd *cmd, t_list *list, t_data *data)
{
	int	nb_args;

	if (ft_fill_cmd_redirs(cmd, data, list))
		return (MEMORY_ERR_NB);
	nb_args = ft_fill_cmd_count_args(list);
	// if (!nb_args)
	// {
	// 	if (ft_fill_cmd_no_agrs(cmd) == MEMORY_ERR_NB)
	// 		return (MEMORY_ERR_NB);
	// }
	// else
	// {
	//printf("nb args : %d\n", nb_args);
	if (nb_args)
	{
		if (ft_fill_cmd_init_tab_args(nb_args, cmd) == MEMORY_ERR_NB)
			return (MEMORY_ERR_NB);
		if (ft_fill_cmd_fill_tab_args(cmd, list, nb_args))
			return (MEMORY_ERR_NB);
	}
	// }
	return (FUNCTION_SUCCESS);
}
