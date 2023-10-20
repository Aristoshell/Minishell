#include "minishell.h"
#include "minishell_louis.h"

// penser a initialiser les currents

bool	ft_check_empty_tokens_list(t_list *list)
{
	t_token	*curr_tok;

	while (list)
	{
		curr_tok = (t_token *)list->content;
		if (curr_tok->empty_node != true)
			return (false);
		list = list->next;
	}
	return (true);
}

void	ft_count_cmd(t_list *list, t_data *data)
{
	t_token	*curr_tok;

	data->nb_command = 1;
	while (list)
	{
		curr_tok = (t_token *)list->content;
		if (curr_tok->type == type_pipe)
			data->nb_command += 1;
		list = list->next;
	}
}

int	ft_init_tab_cmd(t_data *data)
{
	data->cmd = malloc(sizeof(t_cmd) * data->nb_command);
	if (!data->cmd)
		return (MEMORY_ERROR_NB); // attention check retour de cette fonction avant (previously on retournais -1) + effacer ce qui a ete alloue avant
	return (FUNCTION_SUCCESS);
}

void	ft_check_builtin(t_cmd	*cmd)
{
	if (cmd->cmd_args[0])
	{
		if (!ft_strncmp("echo", cmd->cmd_args[0], (ft_strlen("echo") + 1)))
			cmd->cmd_type = cmd_echo;
		else if (!ft_strncmp("cd", cmd->cmd_args[0], (ft_strlen("cd") + 1)))
			cmd->cmd_type = cmd_cd;
		else if (!ft_strncmp("pwd", cmd->cmd_args[0], (ft_strlen("pwd") + 1)))
			cmd->cmd_type = cmd_pwd;
		else if (!ft_strncmp("export", cmd->cmd_args[0], (ft_strlen("export") + 1)))
		{
			if (cmd->cmd_args[1])
				cmd->cmd_type = cmd_export;
			else
				cmd->cmd_type = cmd_export_print;
		}
		else if (!ft_strncmp("unset", cmd->cmd_args[0], (ft_strlen("unset") + 1)))
			cmd->cmd_type = cmd_unset;
		else if (!ft_strncmp("exit", cmd->cmd_args[0], (ft_strlen("exit") + 1)))
			cmd->cmd_type = cmd_exit;
		else
			cmd->cmd_type = no;
	}
	//printf("builtin : %d\n", cmd->cmd_type);
}

int	ft_fill_tab_cmd(t_data *data, t_list *list)
{
	t_token	*curr_token;

	data->current_cmd = 0;
	curr_token = (t_token *)list->content;
	while (data->current_cmd < data->nb_command)
	{
		// printf("current token : %s\n", curr_token->string);
		if (ft_init_cmd(data, data->current_cmd)
			|| ft_fill_cmd(data->cmd[data->current_cmd], list, data))
			return (MEMORY_ERROR_NB);
		if (data->cmd[data->current_cmd]->cmd_args)
			ft_check_builtin(data->cmd[data->current_cmd]);
		data->current_cmd++;
		while (curr_token->type != type_pipe)
		{
			list = list->next;
			if (!list)
				return (FUNCTION_SUCCESS);
			curr_token = (t_token *)list->content;
		}
		list = list->next;
		curr_token = (t_token *)list->content;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_interprete(t_info *info, t_data *data)
{
	data->nb_command = 0;
	// if (ft_check_empty_tokens_list(info->tokens))
	// {
	// 	ft_reinit_data(data);
	// 	return (printf("LINE IS EMPTY\n"), LINE_IS_EMPTY);
	// }
	ft_count_cmd(info->tokens, data);
	//printf("nb cmd : %d\n", data->nb_command);
	if (ft_init_tab_cmd(data) != FUNCTION_SUCCESS)
		return (MEMORY_ERROR_NB);
	if (ft_fill_tab_cmd(data, info->tokens))
		return (MEMORY_ERROR_NB);
	//ft_display_tab_cmd(data);
	return (0);
}
