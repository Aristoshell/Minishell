
#include "minishell.h"
#include "minishell_louis.h"

void	ft_clean_t_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd_args)
		ft_clean_2d_array((void **)cmd->cmd_args, (void *)ft_clean_string);
	if (cmd->path_cmd)
		ft_clean_2d_array((void **)cmd->path_cmd, (void *)ft_clean_string);
	if (cmd->heredoc_name)
		ft_clean_string(&cmd->heredoc_name);
	if (cmd->heredoc_sep)
		ft_clean_string(&cmd->heredoc_sep);
	cmd->fd_in = 0;
	cmd->fd_out = 0;
	free(cmd);
}
