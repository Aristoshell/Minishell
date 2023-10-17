
#include "minishell.h"
#include "minishell_louis.h"

t_envlist	*ft_lst_env_last(t_envlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
