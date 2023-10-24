#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd_count_args(t_list *list)
{
	int		nb_agrs;
	t_token	*curr_token;

	nb_agrs = 0;
	curr_token = (t_token *)list->content;
	while (curr_token->type != type_pipe)
	{
		if (curr_token->type == type_word && !curr_token->redir_file)
			nb_agrs++;
		list = list->next;
		if (!list)
			return (nb_agrs);
		curr_token = list->content;
	}
	return (nb_agrs);
}

int	ft_fill_cmd_no_agrs(t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char *) * (1));
	if (!cmd->cmd_args)
		return (MEMORY_ERR_NB);
	cmd->cmd_args[0] = NULL;
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_init_tab_args(int nb_args, t_cmd *cmd)
{
	cmd->cmd_args = malloc(sizeof(char *) * (nb_args + 1));
	if (!cmd->cmd_args)
		return (MEMORY_ERR_NB);
	return (FUNCTION_SUCCESS);
}

int	ft_fill_cmd_fill_tab_args(t_cmd *cmd, t_list *list, int n_args)
{
	int		i;
	t_token	*curr_token;

	i = 0;
	curr_token = (t_token *)list->content;
	while (i < n_args)
	{
		if (curr_token->type == type_word && !curr_token->empty_node
			&& !curr_token->redir_file)
		{
			cmd->cmd_args[i] = ft_strdup(curr_token->string);
			if (!cmd->cmd_args[i])
				return (MEMORY_ERR_NB);
			i++;
		}
		list = list->next;
		if (!list)
			break ;
		curr_token = list->content;
	}
	cmd->cmd_args[i] = NULL;
	return (FUNCTION_SUCCESS);
}
