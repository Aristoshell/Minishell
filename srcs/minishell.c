
#include "minishell.h"
#include "minishell_louis.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv ;
	if (argc != 1)
		return (perror(DIS_ERR_ARG), 1);
	if (!envp)
		return (perror(DIS_ERR_ENV), 1);
	data = NULL;
	data = ft_create_data(data, envp);
	if (!data)
		return (MEMORY_ERROR_NB); //checker ce que je dois effacer
	if (prompt(data) == MEMORY_ERROR_NB)
		return (MEMORY_ERROR_NB); //add ce que je dois effacer
	if (data)
		ft_clean_t_data(data);
	return (0);
}
