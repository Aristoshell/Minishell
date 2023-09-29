
#include "minishell.h"
#include "minishell_louis.h"

void	ft_display_lexer(t_info info)
{
	int i = 0;
	while(i < info.nb_tokens)
	{
		dprintf(STDERR_FILENO, "[%d] [%d]: %s\n", i, info.tokens[i]->type, info.tokens[i]->string);
		i++;
	}
}
