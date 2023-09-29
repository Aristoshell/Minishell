
#include "minishell.h"
#include "minishell_louis.h"

t_envlist	*ft_lst_env_new(const char *key, char *val)
{
	t_envlist	*newlist;

	newlist = malloc(sizeof(t_envlist));
	if (newlist == NULL)
		return (MEMORY_ERROR_PT);
	newlist->key = key;
	if (val)
		newlist->val = val;
	else
		newlist->val = NULL;
	newlist->flag = 0;
	ft_set_flag(&newlist->flag, val);
	newlist->next = NULL;
	return (newlist);
}
