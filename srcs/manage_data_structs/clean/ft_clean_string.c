
#include "minishell.h"
#include "minishell_louis.h"

long unsigned	ft_strlen(const char *str)
{
	long unsigned	i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

void	ft_clean_string(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	str = NULL;
}
