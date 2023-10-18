#include "minishell.h"
#include "minishell_louis.h"

int	ft_insert_expand_splitted(t_list *list, char *new_word, bool join_next)
{
	t_token	*new_token;
	t_list	*new;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (MEMORY_ERROR_NB);
	new_token->string = new_word;
	new_token->type = type_word;
	new_token->expand = false;
	new_token->join_with_next = join_next; //pb ici, attention pour le dernier ?
	new_token->quote = false;
	new_token->empty_node = false;
	new_token->redir_file = false;
	new = ft_lstnew((void *)new_token);
	if (!new)
		return (MEMORY_ERROR_NB);
	new->next = list->next;
	list->next = new;
	return (FUNCTION_SUCCESS);
}

int	ft_expand_val_split(t_list *list, char *env_val)
{
	char	**splited;
	t_token	*current_token;
	int		i;

	splited = ft_split(env_val, ' ');
	if (!splited)
		return (MEMORY_ERROR_NB);
	current_token = list->content;
	current_token->expand = true; // a checker
	current_token->string = splited[0];
	// if (splited[1])
	// 	current_token->join_with_next = true;
	current_token->join_with_next = false;
	i = 1;
	while (splited && splited[i])
	{
		if (splited[i + 1] || current_token->join_with_next)
			//ft_insert_expand_splitted(list, splited[i], true);
			ft_insert_expand_splitted(list, splited[i], false);
		else
			ft_insert_expand_splitted(list, splited[i], false);
		i++;
		list = list->next;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_expand_val(t_list *list, t_envlist *env, t_data *data)
{
	t_token	*curr_token;
	int		len;

	curr_token = (t_token *)list->content;
	if (curr_token->string[0] == '?')
	{
		free(curr_token->string);
		curr_token->string = ft_strdup(ft_itoa(data->exec_val));//verif retour itoa + ft_strdup en deux fois
	}
	else
	{
		len = ft_strlen(curr_token->string) + 1;
		while (env && ft_strncmp(curr_token->string, (const char *)env->key, len))
			env = env->next;
		free(curr_token->string); //maybe invalide free
		if (!env)
		{
			curr_token->empty_node = true;
			curr_token->string = NULL;
		}
		else if (curr_token->quote == double_q)
		{
			curr_token->string = ft_strdup(env->val);
			if (!curr_token->string)
				return (MEMORY_ERROR_NB);
		}
		else
			ft_expand_val_split(list, env->val); //add verif
	}
	return (FUNCTION_SUCCESS);
}
