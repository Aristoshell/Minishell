
#include "minishell.h"
#include "minishell_louis.h"


/*
retourne la taille du tableau de liste
*/

int	strlen_list(t_cmd **cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (-1);
	while (cmd[i])
		i++;
	return (i);
}
