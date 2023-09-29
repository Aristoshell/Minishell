
#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_cmd_count_args(t_info *info)
{
	int nb_agrs = 0;
	if (info->current_token < info->nb_tokens && info->tokens[info->current_token]->type == type_pipe)
			info->current_token++;
	//printf(GREEN"Current token : %s\n"NC, info->tokens[info->current_token]->string);
	while (info->current_token < info->nb_tokens && info->tokens[info->current_token]->type != type_pipe) //ie. dernier token ou pipe
	{
		nb_agrs++;
		info->current_token++;
	}
	//printf(BLUE"nb args : %d\n"NC, nb_agrs);
	return (nb_agrs);
}
