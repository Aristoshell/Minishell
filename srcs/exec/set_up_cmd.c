
#include "minishell.h"
#include "minishell_louis.h"


/*
appellera le builtin voulu en fonction de la valeurs dans le champ cmd->type
de la struct cmd
*/

int	handle_builtins(t_data *data, t_pipe *pipes)
{
	t_cmd	**cmd;

	cmd = data->cmd;
	if (cmd[data->current_cmd]->cmd_type == no_cmd)
	{
		if (data->exec_val == 130)
			return (130);
		return (1);
	}
	else if (cmd[data->current_cmd]->cmd_type == cmd_echo)
		return (bt_echo(data, data->current_cmd));
	else if (cmd[data->current_cmd]->cmd_type == cmd_cd)
		return (bt_cd(data));
	else if (cmd[data->current_cmd]->cmd_type == cmd_pwd)
		return (bt_pwd(data));
	else if (cmd[data->current_cmd]->cmd_type == cmd_export)
		return (export(&data->envp, cmd[data->current_cmd]->cmd_args));
	else if (cmd[data->current_cmd]->cmd_type == cmd_export_print)
		return (display_export(data->envp, cmd[data->current_cmd]->cmd_args));
	else if (cmd[data->current_cmd]->cmd_type == cmd_unset)
		return (unset(&data->envp, cmd[data->current_cmd]->cmd_args));
	else if (cmd[data->current_cmd]->cmd_type == cmd_env)
		return (display_env(data->envp, cmd[data->current_cmd]->cmd_args));
	else if (cmd[data->current_cmd]->cmd_type == cmd_exit)
		return (bt_exit(data, data->current_cmd, pipes));
	return (0);
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
cette fonction join le path et la commande
*/

bool    ft_special_case(char *cmd)
{
    if (!ft_strncmp(cmd, ".", 2) || !ft_strncmp(cmd, "..", 3) || !ft_strncmp(cmd, "", 1))
        return (true);
    return (false);
}

char    *get_cmd(char **paths, char *cmd)
{
    char    *tmp;
    char    *to_try;
    struct    stat file_info;

    if (ft_special_case(cmd))
        return (g_glb = 127, ft_dprintf(STDERR_FILENO, D_ER_CMD_NF, cmd), NULL); // 127
	else if (!paths || ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
			{
				if (stat(cmd, &file_info) == 0)
                {
                    if (S_ISDIR(file_info.st_mode))
                        return (g_glb = 126, ft_dprintf(STDERR_FILENO, D_ER_ISDIR, cmd), NULL); //126
                }
				return (cmd);
			}
			else
			{
				// ft_dprintf(STDERR_FILENO, "1	");
				return (g_glb = 126, ft_dprintf(STDERR_FILENO, D_ER_PERM, cmd), NULL); //126
			}
		}
		// ft_dprintf(STDERR_FILENO, "2	");
		return (g_glb = 127, ft_dprintf(STDERR_FILENO, D_ER_NO_FILDIR, cmd), NULL); //127
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		to_try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(to_try, F_OK) == 0)
		{
			if (access(to_try, X_OK) == 0)
			{
				// ft_dprintf(STDERR_FILENO, "3	");
				return(to_try);
			}
			else
			{
				// ft_dprintf(STDERR_FILENO, "4	");
				return (g_glb = 126, ft_dprintf(STDERR_FILENO, D_ER_PERM, to_try), NULL); //126
			}
		}
		free(to_try);
		paths++;
	}
	// ft_dprintf(STDERR_FILENO, "5	");
	return (g_glb = 127, ft_dprintf(STDERR_FILENO, D_ER_CMD_NF, cmd), NULL); //127
}
