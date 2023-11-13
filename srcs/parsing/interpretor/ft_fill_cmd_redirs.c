/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_redirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:56:05 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 03:46:01 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

void	ft_clean_t_file(t_files *file)
{
	if (file)
	{
		if (file->filename)
		{
			free(file->filename);
			file->filename = NULL;
		}
		free(file);
		file = NULL;
	}
}

int	ft_fill_cmd_redirs_pipe_in(t_cmd *cmd, t_data *data)
{
	t_files	*redirs;
	t_list	*new;

	if (data->current_cmd != 0)
	{
		redirs = malloc(sizeof(t_files));
		if (!redirs)
			return (MEMORY_ERR_NB);
		redirs->filename = NULL;
		redirs->filetype = pipe_in_;
		redirs->open = false;
		redirs->redirect = false;
		redirs->fd = -1;
		new = ft_lstnew((void *)redirs);
		if (!new)
			return (free(redirs), redirs = NULL, MEMORY_ERR_NB);
		ft_lstadd_back(&cmd->list_files, new);
	}
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_redirs_pipe_out(t_cmd *cmd, t_data *data)
{
	t_files	*redirs;
	t_list	*new;

	if (data->current_cmd != data->nb_command - 1)
	{
		redirs = malloc(sizeof(t_files));
		if (!redirs)
			return (MEMORY_ERR_NB);
		redirs->filename = NULL;
		redirs->filetype = pipe_out_;
		redirs->open = false;
		redirs->redirect = false;
		new = ft_lstnew((void *)redirs);
		if (!new)
			return (free(redirs), redirs = NULL, MEMORY_ERR_NB);
		ft_lstadd_back(&cmd->list_files, new);
	}
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_redirs(t_cmd *cmd, t_data *data, t_list *list)
{
	if (ft_fill_cmd_redirs_pipe_in(cmd, data)
		|| ft_fill_cmd_redirs_pipe_out(cmd, data)
		|| ft_fill_cmd_redirs_files(cmd, list))
		return (MEMORY_ERR_NB);
	return (FUNCTION_SUCCESS);
}
