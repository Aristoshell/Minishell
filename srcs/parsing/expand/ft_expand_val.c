/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_val.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 01:56:43 by marine            #+#    #+#             */
/*   Updated: 2023/11/13 13:57:06 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_insert_expand_splitted(t_list *list, char *new_word, bool join_next)
{
	t_token	*new_token;
	t_list	*new;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (MEMORY_ERR_NB);
	new_token->string = new_word;
	new_token->type = type_word;
	new_token->expand = false;
	new_token->join_with_next = join_next;
	new_token->quote = false;
	new_token->redir_file = false;
	new = ft_lstnew((void *)new_token);
	if (!new)
		return (free(new_token), new_token = NULL, MEMORY_ERR_NB);
	new->next = list->next;
	list->next = new;
	return (FUNCTION_SUCCESS);
}

int	ft_dup_nothing(t_data *data, char **splited)
{
	data->curr_token->string = ft_strdup("\0");
	if (!data->curr_token->string)
		return (ft_free_2d_array(splited), MEMORY_ERR_NB);
	return (ft_free_2d_array(splited), FUNCTION_SUCCESS);
}

int	ft_expand_val_split(t_list *list, char *env_val, t_data *data)
{
	char	**splited;
	int		i;
	bool	mem_last;

	splited = ft_split(env_val, ' ');
	if (!splited)
		return (MEMORY_ERR_NB);
	data->curr_token = list->content;
	data->curr_token->expand = true;
	data->curr_token->string = splited[0];
	mem_last = data->curr_token->join_with_next;
	data->curr_token->join_with_next = false;
	if (!splited[0])
		return (ft_dup_nothing(data, splited));
	i = 1;
	while (splited && splited[i])
	{
		if (ft_insert_expand_splitted(list, splited[i], false))
			return (ft_free_2d_array(splited), splited = NULL, MEMORY_ERR_NB);
		i++;
		list = list->next;
	}
	data->curr_token = (t_token *)list->content;
	free(splited);
	return (data->curr_token->join_with_next = mem_last, FUNCTION_SUCCESS);
}

int	ft_expand_questionmark(t_token *curr_token, t_data *data)
{
	char	*nb;

	free(curr_token->string);
	curr_token->string = NULL;
	nb = ft_itoa(data->exec_val);
	if (!nb)
		return (MEMORY_ERR_NB);
	curr_token->string = nb;
	return (FUNCTION_SUCCESS);
}

int	ft_expand_val(t_list *list, t_envlist *env, t_data *data)
{
	t_token	*curr_token;
	int		len;

	curr_token = (t_token *)list->content;
	if (curr_token->string[0] == '?')
		return (ft_expand_questionmark(curr_token, data));
	len = ft_strlen(curr_token->string) + 1;
	while (env && ft_strncmp(curr_token->string, (const char *)env->key, len))
		env = env->next;
	free(curr_token->string);
	curr_token->string = NULL;
	if (!env)
		curr_token->string = NULL;
	else if (curr_token->quote == double_q)
	{
		curr_token->string = ft_strdup(env->val);
		if (!curr_token->string)
			return (MEMORY_ERR_NB);
	}
	else if (ft_expand_val_split(list, env->val, data))
		return (MEMORY_ERR_NB);
	return (FUNCTION_SUCCESS);
}
