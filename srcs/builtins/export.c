
#include "minishell.h"
#include "minishell_louis.h"

t_envlist *ft_key_exist(t_envlist *env, char *new_key)
{
	while (env)
	{
		if (ft_strncmp(env->key, new_key, (ft_strlen(new_key) + 1)) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	ft_update_curr(t_envlist *new, t_envlist *curr)
{
	if (new->val)
	{
		if (curr->val)
			free (curr->val);
		curr->val = new->val;
		curr->flag = MASK_ENV;
		new->val = NULL;
	}
	free((void *)new->key);
	new->key = NULL;
	free(new);
}

int	export_single(t_envlist **env, char *line)
{
	t_envlist	*new;
	t_envlist	*temp;
	t_envlist	*curr;

	if (!isalpha(line[0]))
		return (ft_error(WRONG_ID_EXPORT, line));
	temp = *env;
	new = ft_new_envvar(line);
	if (!new)
		return (MEMORY_ERR_NB);
	if (!(*env))
		*env = new;
	curr = ft_key_exist(*env, (char *)new->key);
	if (curr)
		ft_update_curr(new, curr);
	else
		ft_lst_env_add_back(env, new);
	(*env) = temp;
	return (FUNCTION_SUCCESS);
}

int	export(t_envlist **env, char **tab)
{
	int	i;

	i = 1;
	while (tab[i])
	{
		if (export_single(env, tab[i]))
			return (MEMORY_ERR_NB);
		i++;
	}
	return (FUNCTION_SUCCESS);
}
