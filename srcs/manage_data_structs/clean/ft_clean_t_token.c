
#include "minishell.h"
#include "minishell_louis.h"

void	ft_clean_t_token(t_token **token)
{
	if (!token || !*token || !(*token)->string)
		return ;
    ft_clean_string(&((*token)->string));
	//token->type = type_default; //enleve car bug
}


/*

de mon ancien code

void	delete_t_tokens(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_tokens)
	{
		if (info->tokens[i])
			free(info->tokens[i]);
		i++;
	}
	info->nb_tokens = 0;
	info->tokens = NULL;
}

*/