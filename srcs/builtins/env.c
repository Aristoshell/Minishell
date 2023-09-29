
#include "minishell.h"
#include "minishell_louis.h"

void	display_env(t_envlist *env)
{
	while (env) // verif si besoin de 
	{
		if (MASK_EXPORT & env->flag && MASK_SET & env->flag)
			ft_dprintf(STDOUT_FILENO, GREEN"%s=%s\n"NC, env->key, env->val);
		if (env->next)
			env = env->next;
		else
			return ;
	}
}
