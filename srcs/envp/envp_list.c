/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:35:36 by madavid           #+#    #+#             */
/*   Updated: 2023/09/15 16:37:39 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_lst_env_delone(t_envlist *lst)
{
	if (lst == NULL)
		return ;
	ft_bzero(lst->key, ft_strlen(lst->key));
	free(lst->key);
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

void	set_flag(int *flag, char *val)
{
	if (val)
		*flag |= var_set | var_exported;
	else
		*flag = var_exported;
}

t_envlist	*ft_lst_env_new(char *key, char *val)
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
