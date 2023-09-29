
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_cmd_separator(char c)
{
	if (c == '|')
		return (true);
	return (false);
}
