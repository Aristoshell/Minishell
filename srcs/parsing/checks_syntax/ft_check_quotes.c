
#include "minishell.h"
#include "minishell_louis.h"

char	ft_check_open_quote(const char *input)
{
	int		i;
	char	delimiter;

	i = 0;
	delimiter = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SIMPLE_QUOTE)
		{
			delimiter = input[i];
			i++;
			while (input[i] && delimiter != 0)
			{
				if (input[i++] == delimiter)
					delimiter = 0;
			}
			if (!input[i] && delimiter != 0)
				return (delimiter);
		}
		else
			i++;
	}
	return (delimiter);
}
