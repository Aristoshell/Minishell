/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:35:36 by madavid           #+#    #+#             */
/*   Updated: 2023/09/18 22:45:00 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_lst_env_delone(t_envlist *lst)
{
	if (lst == NULL)
		return ;
	ft_bzero((void *)lst->key, ft_strlen(lst->key));
	free((void *)lst->key);
	ft_bzero(lst->val, ft_strlen(lst->val));
	free(lst->val);
	lst->flag = 0;
	free(lst);
}

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
}

t_envlist	*ft_lst_env_last(t_envlist *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

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

void	ft_lst_pop(t_envlist **lst, char *key)
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

void	set_flag(int *flag, char *val)
{
	*flag = MASK_EXPORT;
	if (val)
		*flag |= MASK_SET;
}

t_envlist	*ft_lst_env_new(const char *key, char *val)
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
	newlist->flag = 0;
	set_flag(&newlist->flag, val);
	newlist->next = NULL;
	return (newlist);
}
