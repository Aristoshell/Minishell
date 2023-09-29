
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_operator(char c)
{
	if (c == '>' || c == '<' || c == '|') // || (c == '>' && next == '>')|| (c == '<' && next == '<'))
		return (true);
	return (false);
}
