/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:42:36 by lmarchai          #+#    #+#             */
/*   Updated: 2023/09/18 11:20:56 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/*
appellera le builtin voulu en fonction de la valeurs dans le champ cmd->type
de la struct cmd
*/

void	handle_builtins(t_cmd *cmd, t_pipe *pipes, char **envp)
{
	if (!envp || !pipes)
		return ;
	if (cmd->cmd_type == cmd_echo)
		printf("builtin echo");
	if (cmd->cmd_type == cmd_echo_n)
		printf("builtin echo_n");
	if (cmd->cmd_type == cmd_cd)
		printf("builtin cd");
	if (cmd->cmd_type == cmd_pwd)
		printf("builtin pwd");
	if (cmd->cmd_type == cmd_export)
		printf("builtin export");
	if (cmd->cmd_type == cmd_unset)
		printf("builtin unset");
	if (cmd->cmd_type == cmd_env)
		printf("builtin env");
	if (cmd->cmd_type == cmd_exit)
		printf("builtin exit");
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
		return (NULL);
	if (!paths)
		return (nopath(cmd));
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		to_try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(to_try, 0) == 0)
			return (to_try);
		free(to_try);
		paths++;
	}
	return (NULL);
}
