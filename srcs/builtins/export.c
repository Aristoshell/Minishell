
#include "minishell.h"
#include "minishell_louis.h"

t_envlist	*ft_key_exist(t_envlist *env, char *new_key)
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

int	is_forbiden_in_var(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_' && str[i] != '=')
			return (i);
		i++;
	}
	return (0);
}

int	export_single(t_envlist **env, char *line)
{
	t_envlist	*new;
	t_envlist	*temp;
	t_envlist	*curr;

	temp = *env;
	new = ft_new_envvar(line);
	if (!new)
		return (MEMORY_ERR_NB);
	if ((!isalpha(new->key[0]) && new->key[0] != '_')
		|| is_forbiden_in_var(&new->key[1]))
		return (ft_dprintf(STDERR_FILENO, D_ER_EXPAND, line), 1); // free le node (pas encore fait)
	if (!(*env))
		return (*env = new, FUNCTION_SUCCESS);
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
	int	rez;
	int	final_rez;

	i = 1;
	final_rez = 0;
	while (tab[i])
	{
		rez = export_single(env, tab[i]);
		if (rez == MEMORY_ERR_NB)
			return (MEMORY_ERR_NB);
		if (rez == 1)
			final_rez = 1;
		i++;
	}
	return (final_rez);
}
