
#include "minishell.h"
#include "minishell_louis.h"

bool	ft_is_simple_quote(char c)
{
	if (c == '\'')
		return (1);
	return (0);
}

bool	ft_is_double_quote(char c)
{
	if (c == '"')
		return (1);
	return (0);
}

char	ft_is_quote(char c)
{
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return (0);
}
