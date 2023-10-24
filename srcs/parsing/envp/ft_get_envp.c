
#include "minishell.h"
#include "minishell_louis.h"

t_envlist	*ft_get_envp(char **envp)
{
	int			i;
	t_envlist	*list;
	t_envlist	*new;

	i = 0;
	list = NULL;
	if (!envp[0])
		return (NULL);
	while (envp[i])
	{
		new = ft_new_envvar(envp[i]);
		if (!new)
			return (ft_lst_env_clear(&list), MEMORY_ERROR_PT);
		if (!list)
			list = new;
		else
			ft_lst_env_add_back(&list, new);
		i++;
	}
	return (list);
}
