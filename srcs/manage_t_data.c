
#include "minishell.h"
#include "minishell_louis.h"

void	ft_init_data(t_data *data)
{
	data->current_cmd = 0;
	data->nb_command = 0;
	data->cmd = NULL;
	data->tokens = NULL;
}

void	ft_clean_cmd(t_cmd *cmd)
{
	if (cmd->cmd_args)
	{
		//printf("Cleaning cmd args\n");
		ft_free_2d_array(cmd->cmd_args);
		cmd->cmd_args = NULL;
	}
	if (cmd->path_cmd)
	{
		ft_free_2d_array(cmd->path_cmd);
		cmd->path_cmd = NULL;
	}
	if (cmd->list_files)
		ft_lstclear(&cmd->list_files, (void *)ft_clean_t_file);
	free(cmd);
}

void	ft_reinit_data(t_data *data)
{
	int	i;

	if (data->cmd)
	{
		i = 0;
		while (i < data->nb_command)
		{
			ft_clean_cmd(data->cmd[i]);
			data->cmd[i] = NULL;
			i++;
		}
		free(data->cmd);
		data->cmd = NULL;
	}
	if (data->tokens)
		ft_lstclear(&(data)->tokens, (void *)ft_clean_token);
	ft_init_data(data);
	//printf("data reinit\n");
}

void	ft_clean_t_data(t_data *data)
{
	if (!data)
		return ;
	ft_reinit_data(data);
	if (data->envp)
		ft_lst_env_clear(&data->envp);
	data->envp = NULL;
	free(data);
	data = NULL;
	//printf("t_data cleaned\n");
}

t_data	*ft_create_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (MEMORY_ERROR_PT);
	ft_init_data(data);
	data->exec_val = 0;
	data->envp = ft_get_envp(envp);
	if (!data->envp)
		return (ft_clean_t_data(data), MEMORY_ERROR_PT);
	return (data);
}

/* nouvelles fonction */

// void	ft_clean_data_tokens_tab(t_data *data)
// {
// 	int	i;
// 	t_cmd **tab;

// 	i = 0;
// 	tab = data->cmd;
// 	while (i < data->nb_command)
// 	{
// 		if (tab[i])
// 		{
// 			if (tab[i]->string)
// 			{
// 				free(tab[i]->string);
// 				tab[i]->string = NULL;
// 			}
// 			tab[i]->type = type_default;
// 			free((void*)tab[i]);
// 			tab[i] = NULL;
// 			i++;
// 		}
// 	}
// 	free(tab);
// 	tab = NULL;
// } //pas du tout fini mais flemme 

// void	ft_clean_data_bis(t_data *data)
// {
// 	if ((data))
// 	{
// 		data->current_cmd = 0;
// 		data->nb_command = 0;
// 		ft_clean_data_tokens_tab(data);
// 	}
// 	printf("t_data reset\n");
// }

/* fin*/
