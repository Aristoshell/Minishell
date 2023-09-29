
#include "minishell.h"
#include "minishell_louis.h"

/*peut etre quil faut un **info pour bien le clean ?*/

void	ft_clean_t_info(t_info *info)
{
	if (info)
		return ;
	ft_reinit_info(info);
	free(info);
	info = NULL;
}
