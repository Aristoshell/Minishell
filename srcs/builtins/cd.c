/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:12:06 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/16 14:22:51 by lmarchai         ###   ########.fr       */
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

int	update_lines(t_envlist *envp, char old_pwd[PATH_MAX], char pwd[PATH_MAX])
{
	if (ft_strncmp(envp->key, "OLDPWD", 7) == 0)
	{
		free(envp->val);
		envp->val = ft_strdup(old_pwd);
		if (!envp->val)
			return (2);
	}
	if (ft_strncmp(envp->key, "PWD", 4) == 0)
	{
		free(envp->val);
		envp->val = ft_strdup(pwd);
		if (!envp->val)
			return (2);
	}
	return (0);
}

int	update_env(t_envlist *envp, char old_pwd[PATH_MAX], int to_ret)
{
	int		i;
	int		j;
	char	pwd[PATH_MAX];

	pwd[0] = 0;
	i = 0;
	if (!old_pwd)
		return (1);
	j = ft_envlstsize(envp);
	getcwd(pwd, PATH_MAX);
	if (pwd[0] == 0)
		return (2);
	while (i < j)
	{
		if (update_lines(envp, old_pwd, pwd) == 2)
			return (2);
		envp = envp->next;
		i++;
	}
	return (to_ret);
}

int	go_to(t_cmd *cmd, int nbr_arg, t_envlist *envp, char **env)
{
	char		cwd[PATH_MAX];
	struct stat	file_info;

	cwd[0] = 0;
	getcwd(cwd, PATH_MAX);
	if (cwd[0] == 0)
		return (1);
	if (!env)
		return (1);
	if (nbr_arg == 0)
	{
		if (chdir(find_home(env)) == -1)
			return (1);
	}
	if (cmd->cmd_args && cmd->cmd_args[0] && cmd->cmd_args[1])
	{
		if (stat(cmd->cmd_args[1], &file_info) == 0 \
			&& !S_ISDIR(file_info.st_mode))
			return (ft_dprintf(2, A, cmd->cmd_args[1]), 1);
		if (chdir(cmd->cmd_args[1]) == -1)
			return (manage_errno(cmd->cmd_args[1]), 1);
	}
	return (update_env(envp, cwd, 0));
}

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
			ft_dprintf(2, "minishell: cd: too many arguments\n");
			return (ft_free_2d_array(env), 1);
		}
		return (ft_free_2d_array(env), go_to(cmd, 1, data->envp, env));
	}
	if (!find_home(env))
	{
		ft_dprintf(2, "minishell: cd: HOME not set\n");
		return (ft_free_2d_array(env), 1);
	}
	go_to(cmd, 0, data->envp, env);
	return (ft_free_2d_array(env), 0);
}
