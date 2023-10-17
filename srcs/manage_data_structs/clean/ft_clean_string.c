
#include "minishell.h"
#include "minishell_louis.h"


void	ft_clean_string(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	str = NULL;
}
