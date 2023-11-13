/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_redirs2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:56:05 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 11:33:06 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_get_name_redir_file(t_token *curr_tok, t_files *redir)
{
	if (redir->filetype != ambiguous_in && redir->filetype != ambiguous_out)
	{
		curr_tok->redir_file = true;
		redir->filename = ft_strdup(curr_tok->string);
		if (!redir->filename)
		{
			free(redir);
			redir = NULL;
			return (MEMORY_ERR_NB);
		}
	}
	return (FUNCTION_SUCCESS);
}

void	ft_check_ambigi_redir(t_list *list, t_token *curr_tok, t_files *redir)
{
	while (list && !curr_tok->string)
	{
		if (!curr_tok->join_with_next)
		{
			if (redir->filetype == append_ || redir->filetype == file_to)
				redir->filetype = ambiguous_out;
			else
				redir->filetype = ambiguous_in;
			redir->filename = NULL;
			curr_tok->redir_file = true;
		}
		list = list->next;
		if (list)
			curr_tok = (t_token *)list->content;
	}
}

int	ft_find_redir_token(t_list *list, t_token *curr_tok)
{
	while (list && curr_tok->type < type_from)
	{
		list = list->next;
		if (!list)
			return (STOP);
		curr_tok = (t_token *)list->content;
		if (curr_tok->type == type_pipe)
			return (STOP);
	}
	return (FUNCTION_SUCCESS);
}

t_files	*ft_create_new_redir(t_token *curr_tok)
{
	t_files	*redir;

	redir = malloc(sizeof(t_files));
	if (!redir)
		return (MEMORY_ERROR_PT);
	redir->filetype = (t_filetype)curr_tok->type - 1;
	redir->open = false;
	redir->redirect = false;
	return (redir);
}

int	ft_fill_cmd_redirs_files(t_cmd *cmd, t_list *list)
{
	t_token	*curr_tok;
	t_files	*redir;
	t_list	*new;

	curr_tok = (t_token *)list->content;
	while (list && curr_tok->type != type_pipe)
	{
		if (ft_find_redir_token(list, curr_tok) == STOP)
			return (FUNCTION_SUCCESS);
		redir = ft_create_new_redir(curr_tok);
		if (!redir)
			return (MEMORY_ERR_NB);
		list = list->next;
		curr_tok = (t_token *)list->content;
		ft_check_ambigi_redir(list, curr_tok, redir);
		if (ft_get_name_redir_file(curr_tok, redir))
			return (MEMORY_ERR_NB);
		new = ft_lstnew((void *)redir);
		if (!new)
		{
			free(redir->filename);
			redir->filename = NULL;
			return (free(redir), redir = NULL, MEMORY_ERR_NB);
		}
		ft_lstadd_back(&cmd->list_files, new);
	}
	return (FUNCTION_SUCCESS);
}
