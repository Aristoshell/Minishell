
#include "minishell.h"
#include "minishell_louis.h"

void	ft_lst_env_pop(t_envlist **lst, char *key)
{
	t_envlist	*prev;
	t_envlist	*next;
	t_envlist	*curr;

	prev = NULL;
	curr = (*lst);
	next = NULL;
	if (!(*lst) || !key)
		return ;
	while (curr->next && ft_strcmp(key, curr->key))
	{
		prev = curr;
		curr = curr->next;
	}
	if (!prev) // trouve mais premier maillon
		(*lst) = (*lst)->next;
	else // trouve
	{
		if (!curr || ft_strcmp(key, curr->key)) // pas trouve
			return ;
		next = curr->next;
	}
	ft_lst_env_delone(curr);
	if (prev)
		prev->next = next;
}
