
#include "minishell.h"
#include "minishell_louis.h"

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
