
#include "minishell.h"
#include "minishell_louis.h"

void	ft_lst_env_add_front(t_envlist **lst, t_envlist *new)
{
	if (lst != NULL)
	{
		if (*lst != NULL)
		{
			new->next = (*lst);
		}
		*lst = new;
	}
}
