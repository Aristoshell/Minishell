
#include "minishell.h"
#include "minishell_louis.h"

int	ft_error(int err_code)
{
	if (err_code == MEMORY_ERROR_NB)
		ft_dprintf(STDERR_FILENO, "Problem with memory allocation\n");
	else if (err_code == SYNTAX_QUOTE_ERROR)
		ft_dprintf(STDERR_FILENO, DIS_ERR_SYNTAX_QUOTE);
	else if (err_code == SYNTAX_TOKEN_ERROR)
		ft_dprintf(STDERR_FILENO, RED DIS_ERR_SYNTAX_TOKEN NC);
	//fonction pour supprimer data et ou info (on peut ajouter une secu pour voir sils existent bien mais normalement la secu est integre dans les fonctions que jai codees, tester + faut il envoyer **data et **info ou *data et *info???)
	return (0);
}
