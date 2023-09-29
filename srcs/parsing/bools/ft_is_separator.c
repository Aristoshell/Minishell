
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_separator(char c)
{
	if (ft_is_operator(c) || ft_is_space(c))
		return (true);
	return (false);
}
