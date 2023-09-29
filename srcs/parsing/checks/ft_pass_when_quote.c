
#include "minishell.h"
#include "minishell_louis.h"

void	ft_pass_when_quote(const char *str, int *i)
{
	char	quote;

	while (str[*i])
	{
		quote = str[*i];
			*i += 1;
		while (str[*i] != quote)
			*i += 1;
		*i += 1;
		if (!ft_is_quote(str[*i]))
			return ;
	}
}