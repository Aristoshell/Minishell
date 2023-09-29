
#include "minishell.h"
#include "minishell_louis.h"

void	ft_print_env(t_envlist *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->val);
		env = env->next;
	}
}
