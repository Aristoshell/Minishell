
#include "minishell.h"
#include "minishell_louis.h"

int	unset(t_envlist **env, char **key)
{
	int	i;

	i = 1;
	while (key[i])
	{
		ft_lst_env_pop(env, key[i]);
		i++;
	}
	return (FUNCTION_SUCCESS);
}
