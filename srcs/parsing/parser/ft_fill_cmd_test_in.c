
#include "minishell.h"
#include "minishell_louis.h"

void	ft_fill_cmd_test_in(t_cmd *cmd, t_info *info, t_in_out out_prev, bool first)
{
	if (!first && out_prev == pipe_)
	{
		cmd->input = pipe_; // ca ca sera a change car si on a des redir, la pipe marche plus, ou alors, je laisserai Louis le changer
		info->current_token++;
	}
}
