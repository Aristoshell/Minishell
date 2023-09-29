
#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd_init_tab_args(int nb_args, t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd->cmd_args)
		return (MEMORY_ERROR_NB);
	return (FUNCTION_SUCCESS);
}
