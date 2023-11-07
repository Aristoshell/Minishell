
#include "minishell.h"
#include "minishell_louis.h"

t_envlist		// printf("tokens cleaned\n");
	// printf("tokens cleaned\n");
*ft_key_exist(t_envlist *env, char *new_key)
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

int	is_forbiden_in_var(char *str)
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

	if ((!isalpha(line[0]) && line[0] != '_') || is_forbiden_in_var(&line[1]))
		return (ft_dprintf(STDERR_FILENO, D_ER_EXPAND, line), 2);
	temp = *env;
	new = ft_new_envvar(line);
	if (!new)
		return (MEMORY_ERR_NB);
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
		if (rez == 2)
			final_rez = 2;
		i++;
	}
	return (final_rez);
}
