
#include "minishell.h"
#include "minishell_louis.h"

void	ft_lst_env_add_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*temp;

	if (*lst != NULL)
	{
		temp = ft_lst_env_last(*lst);
		temp->next = new;
	}
	else
		*lst = new ;
}
