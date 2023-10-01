
#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd_fill_tab_args(t_cmd *cmd, t_info *info, int nb_args)
{
	int i = 0;
	info->current_token -= nb_args;
	while (i < nb_args)
	{
		cmd->cmd_args[i] = ft_strdup((const char*)info->tokens[info->current_token]->string);
		if (!cmd->cmd_args[i])
			return (MEMORY_ERROR_NB); // GRRRRR
		i++;
		info->current_token++;
	}
	cmd->cmd_args[i] = malloc(sizeof(char) * 1);	
	if (!cmd->cmd_args[i])
		return (MEMORY_ERROR_NB); // GRRRRR
	cmd->cmd_args[i] = NULL;
	return (FUNCTION_SUCCESS);
}
