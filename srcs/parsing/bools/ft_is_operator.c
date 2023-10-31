
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}
