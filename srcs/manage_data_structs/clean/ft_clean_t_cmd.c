
#include "minishell.h"
#include "minishell_louis.h"

void	ft_clean_file(t_files *file)
{
	if (file->filename)
		free(file->filename);
	free(file);
}

void	ft_clean_t_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd_args)
		ft_clean_2d_array((void **)cmd->cmd_args, (void *)ft_clean_string);
	if (cmd->path_cmd)
		ft_clean_2d_array((void **)cmd->path_cmd, (void *)ft_clean_string);
	ft_lstclear(&(*cmd).list_files, (void *)ft_clean_file);
	free(cmd);
}
