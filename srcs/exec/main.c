
#include "minishell.h"
#include "minishell_louis.h"


/*
creation des arguments des listes qu'on vas utiliser
*/

int	main(int argc, char **argv, char **envp)
{
	t_cmd	**cmd;

	//heredoc_signals_test();
	cross_array_list(cmd, envp);
	return (1);
}
