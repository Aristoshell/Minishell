
#include "minishell.h"
#include "minishell_louis.h"

void	ft_count_cmd(t_info info, t_data *data)
{
	int		i;

	i = 0;
	data->nb_command = 1;
	while (i < info.nb_tokens)
	{
		if (info.tokens[i]->type == type_pipe)
			data->nb_command++;
		i++;
	}
}
