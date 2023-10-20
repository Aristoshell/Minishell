
#include "minishell.h"
#include "minishell_louis.h"

// la fonction va pas car je dois checker si la variable existe pas deja et aussi changer ses settings,
// si "export OMG" mais que omg existe deja et quon lui reassigne aucune valeur, on necrase pas sa valeur
// si "export OMG=" la on met aucune valeur (mais elle reste dans lenv, parce que ca va juste bzero mon char * ou malloc size of char  *1 = \0)
// penser a bien checker les flags
// attention !!!! je peux donner plusieurs arg a export ; ex = export hihi bla blu

int	export(t_envlist **env, char *line)
{
	t_envlist	*new;

	printf("%s\n",line);
	new = ft_new_envvar(line);
	if (!new)
		return (-1);
	if (!(*env))
		*env = new;
	while ((*env))
	{
		if (strcmp((*env)->key, new->key) == 0)
		{
			if (new->val != NULL)
			{
				ft_lst_env_delone(*env);
				ft_lst_env_add_back(env, new);
			}
		}
		(*env) = (*env)->next;
	}
	return (0);
}

