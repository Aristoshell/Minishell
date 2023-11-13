/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_redirs2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:08:19 by madavid           #+#    #+#             */
/*   Updated: 2023/11/13 16:15:58 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_add_redir_list(t_files *redir, t_token *curr_tok, t_cmd *cmd)
{
	t_list	*new;

	if (redir->filetype != ambiguous_in && redir->filetype != ambiguous_out)
	{
		curr_tok->redir_file = true;
		redir->filename = ft_strdup(curr_tok->string);
		if (!redir->filename)
			return (free(redir), MEMORY_ERR_NB);
	}
	redir->open = false;
	redir->redirect = false;
	new = ft_lstnew((void *)redir);
	if (!new)
		return (free(redir->filename), free(redir), MEMORY_ERR_NB);
	ft_lstadd_back(&cmd->list_files, new);
	return (FUNCTION_SUCCESS);
}

void	ft_check_ambigious(t_token *curr_tok, t_files *redir)
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
}

static int	handle_redir_type(t_files **redir, t_token *curr_tok)
{
	*redir = malloc(sizeof(t_files));
	if (!(*redir))
		return (MEMORY_ERR_NB);
	(*redir)->filetype = (t_filetype)curr_tok->type - 1;
	return (FUNCTION_SUCCESS);
}

static int	handle_redir_list(t_files *redir, t_cmd *cmd, \
t_token *curr_tok, t_list *list)
{
	while (curr_tok && !curr_tok->string)
	{
		ft_check_ambigious(curr_tok, redir);
		list = list->next;
		if (list)
			curr_tok = (t_token *)list->content;
	}
	if (ft_add_redir_list(redir, curr_tok, cmd))
		return (MEMORY_ERR_NB);
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_redirs_files(t_cmd *cmd, t_list *list)
{
	t_token	*curr_tok;
	t_files	*redir;

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
		if (handle_redir_type(&redir, curr_tok) != FUNCTION_SUCCESS)
			return (MEMORY_ERR_NB);
		list = list->next;
		curr_tok = (t_token *)list->content;
		if (handle_redir_list(redir, cmd, curr_tok, list) != FUNCTION_SUCCESS)
			return (MEMORY_ERR_NB);
	}
	return (FUNCTION_SUCCESS);
}
