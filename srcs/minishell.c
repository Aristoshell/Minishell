
#include "minishell.h"
#include "minishell_louis.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv ;
	if (argc != 1)
		return (ft_error(WRONG_NB_ARG, NULL));
	if (!envp && !envp[0])
		return (ft_error(NO_ENV, NULL)); // bien vérifier
	data = NULL;
	data = ft_create_data(envp);
	if (!data)
		return (ft_error(MEMORY_ERR_NB, NULL), MEMORY_ERR_NB);
	if (prompt(data) == MEMORY_ERR_NB)
		return (ft_clean_t_data(data), MEMORY_ERR_NB);
	return (0);
}
