
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_check_empty_line(const char *str, int i)
{
	while (str[i])
	{
		if (str[i] > 32)
			return (true);
		i++;
	}
	return (false);
}
