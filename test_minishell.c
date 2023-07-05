/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 17:52:19 by lmarchai          #+#    #+#             */
/*   Updated: 2023/07/05 19:57:55 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

//exec one cmd

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	int				len_tot;
	unsigned int	i;
	char			*res;

	len_tot = strlen(s1) + strlen(s2);
	res = malloc(sizeof (char) * len_tot + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		res[i + strlen(s1)] = s2[i];
		i++;
	}
	res[len_tot] = '\0';
	return (res);
}

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

char *get_args(t_cmd cmd, char **argv)
{
    int i; 
    char *final;
    char space;

    i = 2;
    space = ' ';
    final = strdup(argv[1]);
    final = strncat(final, &space, 1);
    while (argv[i] != NULL)
    {
        final = ft_strjoin(final, argv[i]);
        final = strncat(final, &space, 1);
        i++;
    }
    return (final);
}

void    child_process(t_cmd cmd, char **argv, char **envp)
{
    cmd.paths = find_path(envp);
    cmd.cmd_paths = ft_split(cmd.paths, ':');
    cmd.cmd_args = ft_split(get_args(cmd, argv), ' ');
    cmd.cmd = get_cmd(cmd.cmd_paths, cmd.cmd_args[0]);
    if(!cmd.cmd)
    {
        printf("cmd error\n");
        exit(1);
    }
    execve(cmd.cmd, cmd.cmd_args, envp);
}

int main(int argc, char **argv, char **envp)
{
    t_cmd   cmd;

    cmd.pid1 = fork();
    if(cmd.pid1 == 0)
        child_process(cmd, argv, envp);
    waitpid(cmd.pid1,0,0);
    return 0;
}