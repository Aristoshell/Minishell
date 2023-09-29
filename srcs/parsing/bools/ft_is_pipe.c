
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}
