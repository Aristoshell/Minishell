
#include "minishell.h"
#include "minishell_louis.h"

void	ft_lst_env_clear(t_envlist **lst)
{
	t_envlist	*p;

	if (lst)
	{
		p = *lst;
		while (*lst)
		{
			p = (*lst)->next;
			ft_lst_env_delone(*lst);
			*lst = p;
		}
	}
	printf("Env cleaned\n");
}
