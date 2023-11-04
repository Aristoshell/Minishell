
#include "minishell.h"
#include "minishell_louis.h"

int	display_env(t_envlist *env, char **args)
{
	if (args[1])
		return (ft_dprintf(STDOUT_FILENO, D_ER_ENV, args[1]), 2);
	while (env)
	{
		if (MASK_EXPORT & env->flag && MASK_SET & env->flag)
			ft_dprintf(STDOUT_FILENO, "%s=%s\n", env->key, env->val);
		if (env->next)
			env = env->next;
		else
			break ;
	}
	return (0);
}
