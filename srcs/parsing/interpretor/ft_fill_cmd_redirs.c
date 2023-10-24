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

int	ft_fill_cmd_redirs_files(t_cmd *cmd, t_list *list)
{
	t_token	*curr_tok;//ici je gererais le ambigious
	t_files	*redir;
	t_list	*new;

	curr_tok = (t_token *)list->content;
	while (list && curr_tok->type != type_pipe)
	{
		while (list && curr_tok->type < type_from)
		{
			list = list->next;
			if (!list)
				return (FUNCTION_SUCCESS);
			curr_tok = (t_token *)list->content;
			if (curr_tok->type == type_pipe)
				return (FUNCTION_SUCCESS);
		}
		redir = malloc(sizeof(t_files));
		if (!redir)
			return (MEMORY_ERR_NB);
		redir->filetype = (t_filetype)curr_tok->type - 1;
		list = list->next;
		curr_tok = (t_token *)list->content;
		while (list && curr_tok->empty_node)
		{
			if (!curr_tok->join_with_next)
			{
				redir->filetype = ambiguous;
				redir->filename = NULL;
				curr_tok->redir_file = true;
			}
				list = list->next;
				if (list)
					curr_tok = (t_token *)list->content;
		}
		if (redir->filetype != ambiguous)
		{
			curr_tok->redir_file = true;
			redir->filename = ft_strdup(curr_tok->string);
			if (!redir->filename)
				return (free(redir), redir = NULL, MEMORY_ERR_NB);
		}
		redir->open = false;
		redir->redirect = false;
		new = ft_lstnew((void *)redir);
		if (!new)
			return (free(redir->filename), redir->filename = NULL, free(redir), redir = NULL, MEMORY_ERR_NB);
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
