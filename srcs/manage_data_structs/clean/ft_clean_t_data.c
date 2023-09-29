
#include "minishell.h"
#include "minishell_louis.h"

/*peut etre quil faut un **data pour bien le clean ?*/

void	ft_clean_t_data(t_data *data)
{
	if (!data)
		return ;
	//ft_clean_string(data->input); //jenleve vu que ca fait bugger
	if (data->envp)
		ft_lst_env_clear(&data->envp);
	free(data);
	data = NULL;
	printf("t_data cleaned\n");
}
