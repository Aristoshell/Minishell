/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:12:06 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/12 17:31:20 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

char	*find_home(char **envp)
{
	if (!envp[0])
		return (NULL);
	while (ft_strncmp("HOME", *envp, 4))
	{
		envp++;
		if (!*envp)
			return (NULL);
	}
	return (*envp + 5);
}

int	update_env(t_envlist *envp, char *old_pwd)
{
	int		i;
	int		j;
	char	pwd[PATH_MAX];

	i = 0;
	if (!old_pwd)
		return (0);
	j = ft_envlstsize(envp);
	getcwd(pwd, PATH_MAX);
	while (i < j)
	{
		if (ft_strncmp(envp->key, "OLDPWD", 7) == 0)
		{
			free(envp->val);
			envp->val = ft_strdup(pwd);
		}
		if (ft_strncmp(envp->key, "PWD", 4) == 0)
		{
			free(envp->val);
			envp->val = ft_strdup(pwd);
		}
		envp = envp->next;
		i++;
	}
	return (0);
}

int	go_to(t_cmd *cmd, int nbr_arg, t_envlist *envp, char **env)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (!env)
		return (1);
	if (nbr_arg == 0)
	{
		if (chdir(find_home(env)) == -1)
		{
			update_env(envp, cwd);
			return (1);
		}
	}
	if (cmd->cmd_args && cmd->cmd_args[0] && cmd->cmd_args[1] \
		&& chdir(cmd->cmd_args[1]) == -1)
	{
		update_env(envp, cwd);
		return (1);
	}
	update_env(envp, cwd);
	return (0);
}

/*
arg jamais pris en compte il faut 
*/

int	bt_cd(t_data *data)
{
	t_cmd	*cmd;
	char	**env;

	env = list_to_array(data->envp);
	cmd = data->cmd[data->current_cmd];
	if (cmd->cmd_args[1])
	{
		if (cmd->cmd_args[2])
		{
			ft_dprintf(2, "too many arguments\n");
			return (ft_free_2d_array(env), 1);
		}
		return (ft_free_2d_array(env), go_to(cmd, 1, data->envp, env));
	}
	if (!find_home(env))
	{
		ft_dprintf(2, "HOME not set\n");
		return (ft_free_2d_array(env), 1);
	}
	go_to(cmd, 0, data->envp, env);
	return (ft_free_2d_array(env), 0);
}
