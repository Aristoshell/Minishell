
#include "minishell.h"
#include "minishell_louis.h"


/*
appellera le builtin voulu en fonction de la valeurs dans le champ cmd->type
de la struct cmd
*/

void	handle_builtins(t_data *data)
{
	t_cmd	**cmd;

	cmd = data->cmd;
	if (cmd[data->current_cmd]->cmd_type == no_cmd)
		return ;
	if (cmd[data->current_cmd]->cmd_type == cmd_echo)
		bt_echo(data, data->current_cmd);
	if (cmd[data->current_cmd]->cmd_type == cmd_cd)
		bt_cd(data);
	if (cmd[data->current_cmd]->cmd_type == cmd_pwd)
		bt_pwd();
	if (cmd[data->current_cmd]->cmd_type == cmd_export)
		export(&data->envp, cmd[data->current_cmd]->cmd_args);
	if (cmd[data->current_cmd]->cmd_type == cmd_export_print)
		display_export(data->envp);
	if (cmd[data->current_cmd]->cmd_type == cmd_unset)
		unset(&data->envp, cmd[data->current_cmd]->cmd_args);
	if (cmd[data->current_cmd]->cmd_type == cmd_env)
		display_env(data->envp);
	if (cmd[data->current_cmd]->cmd_type == cmd_exit)
		bt_exit(data, data->current_cmd);
}

/*
recup la variable d'env PATH
*/

char	*find_path(char **envp)
{
	if (!envp[0])
		return (NULL);
	while (strncmp("PATH", *envp, 4))
	{
		envp++;
		if (!*envp)
			return (NULL);
	}
	return (*envp + 5);
}

/*
si on a aucun path cette fonction est appellee permet de gerer les chemin absolu
*/

char	*nopath(char *cmd)
{
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			return (cmd);
		}
	}
	return (NULL);
}

/*
cette fonction join le path et la commande
*/

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*to_try;

	if (!cmd)
		return (/*printf("1\n"), */NULL);
	if (!paths)\
		return (/*printf("2\n"), */nopath(cmd));
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (/*printf("3\n"), */cmd);
		return (/*printf("4\n"), */cmd);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		to_try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(to_try, 0) == 0)
			return (/*printf("5\n"), */to_try);
		free(to_try);
		paths++;
	}
	return (/*printf("6\n"), */cmd);
}
