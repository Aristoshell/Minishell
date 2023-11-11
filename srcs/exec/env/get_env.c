
#include "minishell.h"
#include "minishell_louis.h"

int	ft_envlstsize(t_envlist *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (lst->flag == MASK_ENV)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	*join_lign_env(t_envlist *list)
{
	size_t		i;
	size_t		j;
	char		*ret;

	ret = malloc(sizeof(char) * ft_strlen(list->key) \
		+ ft_strlen(list->val) + 2);
	i = 0;
	j = 0;
	while (i < ft_strlen(list->key))
	{
		ret[i] = list->key[i];
		i++;
	}
	ret[i] = '=';
	i++;
	while (j < ft_strlen(list->val))
	{
		ret[i + j] = list->val[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	**list_to_array(t_envlist *list)
{
	int		i;
	int		j;
	char	**ret;

	i = ft_envlstsize(list);
	ret = ft_calloc(i + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		if (list->flag == MASK_ENV)
		{
			ret[j] = join_lign_env(list);
			j++;
		}
		list = list->next;
	}
	ret[j] = NULL;
	return (ret);
}

void	free_envp(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}
