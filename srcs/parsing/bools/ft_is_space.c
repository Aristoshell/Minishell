
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_space(char c)
{
	if (c == 32 || c == 9)
		return (true);
	return (false);
}
