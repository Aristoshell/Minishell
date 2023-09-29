
#include "minishell.h"
#include "minishell_louis.h"

int	ft_init_tab_cmd(t_data *data)
{
	data->cmd = malloc(sizeof(t_cmd) * data->nb_command);
	if (!data->cmd)
		return (MEMORY_ERROR_NB); // attention check retour de cette fonction avant (previously on retournais -1) + effacer ce qui a ete alloue avant
	return (FUNCTION_SUCCESS);
}
