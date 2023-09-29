
#include "minishell.h"
#include "minishell_louis.h"

int	unset(t_envlist **env, char *key)
{
	ft_lst_env_pop(env, key);
	return (0);
}
