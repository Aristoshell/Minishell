
#include "minishell.h"
#include "minishell_louis.h"

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

bool	ft_special_case(char *cmd)
{
	if (!ft_strncmp(cmd, ".", 2) || !ft_strncmp(cmd, "..", 3)
		|| !ft_strncmp(cmd, "", 1))
		return (true);
	return (false);
}

int	check_access(t_cmd *cmd)
{
	struct stat	file_info;

	file_info = NULL;
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			if (stat(cmd, &file_info) == 0)
			{
				if (S_ISDIR(file_info.st_mode))
					return (g_glb = 126, ft_dprintf(2, D_ER_ISDIR, cmd), NULL); //126
			}
			return (cmd);
		}
		else
			return (g_glb = 126, ft_dprintf(2, D_ER_PERM, cmd), NULL); //126
	}
	ft_dprintf(2, D_ER_NO_FILDIR, cmd);
	return (g_glb = 127, NULL); //127
}

/*
cette fonction join le path et la commande
*/

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*to_try;

	if (ft_special_case(cmd))
		return (g_glb = 127, ft_dprintf(2, D_ER_CMD_NF, cmd), NULL); // 127
	else if (!paths || ft_strchr(cmd, '/'))
		return (check_access());
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");//verif
		to_try = ft_strjoin(tmp, cmd);//verif
		free(tmp);
		if (access(to_try, F_OK) == 0)
		{
			if (access(to_try, X_OK) == 0)
				return (to_try);
			else
				return (g_glb = 126, ft_dprintf(2, D_ER_PERM, to_try), NULL); //126
		}
		free(to_try);
		paths++;
	}
	return (g_glb = 127, ft_dprintf(2, D_ER_CMD_NF, cmd), NULL); //127
}
