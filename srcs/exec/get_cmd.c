/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:32:20 by lmarchai          #+#    #+#             */
/*   Updated: 2023/11/11 14:35:21 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

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

bool	ft_special_case(char *cmd)
{
	if (!ft_strncmp(cmd, ".", 2) || \
		!ft_strncmp(cmd, "..", 3) || !ft_strncmp(cmd, "", 1))
		return (true);
	return (false);
}

char	*parcour_paths(char **paths, char *cmd)
{
	char		*to_try;
	char		*tmp;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		to_try = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(to_try, F_OK) == 0)
		{
			if (access(to_try, X_OK) == 0)
				return (to_try);
			else
				return (g_glb = 126, \
					ft_dprintf(STDERR_FILENO, D_ER_PERM, to_try), NULL);
		}
		free(to_try);
		paths++;
	}
	return (g_glb = 127, \
		ft_dprintf(STDERR_FILENO, D_ER_CMD_NF, cmd), NULL);
}

char	*get_cmd_no_path(char *cmd)
{
	struct stat	file_info;

	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			if (stat(cmd, &file_info) == 0)
			{
				if (S_ISDIR(file_info.st_mode))
					return (g_glb = 126, \
						ft_dprintf(STDERR_FILENO, \
						D_ER_ISDIR, cmd), NULL);
			}
			return (cmd);
		}
		else
			return (g_glb = 126, \
				ft_dprintf(STDERR_FILENO, D_ER_PERM, cmd), NULL);
	}
	return (g_glb = 127, \
		ft_dprintf(STDERR_FILENO, D_ER_NO_FILDIR, cmd), NULL);
}

char	*get_cmd(char **paths, char *cmd)
{
	if (ft_special_case(cmd))
		return (g_glb = 127, ft_dprintf(STDERR_FILENO, \
			D_ER_CMD_NF, cmd), NULL);
	else if (!paths || ft_strchr(cmd, '/'))
		return (get_cmd_no_path(cmd));
	return (parcour_paths(paths, cmd));
}
