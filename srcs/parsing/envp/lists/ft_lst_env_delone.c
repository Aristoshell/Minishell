
#include "minishell.h"
#include "minishell_louis.h"

void	ft_lst_env_delone(t_envlist *lst)
{
	if (lst == NULL)
		return ;
	free((void *)lst->key);
	lst->key = NULL;
	if (lst->val)
	{
		free(lst->val);
		lst->val = NULL;
	}
	lst->flag = 0;
	free(lst);
	lst = NULL;
}
