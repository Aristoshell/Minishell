
#include "minishell.h"
#include "minishell_louis.h"

void	ft_fill_cmd_test_out(t_cmd *cmd, t_info *info)
{
	if (info->current_token < info->nb_tokens && info->tokens[info->current_token]->type == type_pipe)
		cmd->output = pipe_;
}