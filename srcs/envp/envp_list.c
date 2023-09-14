/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:35:36 by madavid           #+#    #+#             */
/*   Updated: 2023/09/14 20:22:47 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* A mettre dans mon .h*/

typedef struct s_envlist
{
	char				*key;
	char				*val;
	int					flag;
	struct s_envlist	*next;
}					t_envlist;

# define var_set 0b0000001
# define var_exported 0b00000010

/* Fin */

void	ft_lstadd_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*temp;

	if (*lst != NULL)
	{
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
	else
		*lst = new ;
}
void	ft_lstdelone(t_envlist *lst)
{
	if (lst == NULL)
		return ;
	ft_bzero(lst->key, ft_strlen(lst->key));
	free(lst->key);
	ft_bzero(lst->val, ft_strlen(lst->val));
	free(lst->val);
	lst->flag = 0;
	free(lst->key);
	free(lst);
}

void	ft_lstclear(t_envlist **lst)
{
	t_envlist	*p;

	if (lst)
	{
		p = *lst;
		while (*lst)
		{
			p = (*lst)->next;
			ft_lstdelone(*lst);
			*lst = p;
		}
	}
}

t_envlist	*ft_lstlast(t_envlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	set_flag(int *flag, char *val)
{
	if (val)
		*flag |= var_set + var_exported;
	else
		*flag = var_exported;
}

t_envlist	*ft_lstnew(char *key, char *val)
{
	t_envlist	*newlist;

	newlist = malloc(sizeof(t_envlist));
	if (newlist == NULL)
		return (NULL);
	newlist->key = key;
	if (val)
		newlist->val = val;
	else
		newlist->val = NULL;
	set_flag(&newlist->flag, val);
	newlist->next = NULL;
	return (newlist);
}
