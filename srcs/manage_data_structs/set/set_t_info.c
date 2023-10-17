
#include "minishell.h"
#include "minishell_louis.h"

void	ft_init_info(t_info *info)
{
	info->nb_tokens = 0; // a delete
	info->current_token = 0; // a delete
	info->tokens = NULL;
}
void	ft_reinit_info(t_info *info)
{
	ft_init_info(info);
	if ((info)->tokens)
	{
		printf("TEST\n");
		ft_clean_2d_array_struct((void ***)&info->tokens, (void *)ft_clean_t_token);
	}
}
/* Nouvelles fonctions */

// void	ft_clean_info_tokens(t_info *info)
// {
// 	int	i;
// 	t_token **tab;

// 	i = 0;
// 	tab = info->tokens;
// 	while (i < info->nb_tokens)
// 	{
// 		if (tab[i])
// 		{
// 			if (tab[i]->string)
// 			{
// 				free(tab[i]->string);
// 				tab[i]->string = NULL;
// 			}
// 			tab[i]->type = type_default;
// 			free((void*)tab[i]);
// 			tab[i] = NULL;
// 			i++;
// 		}
// 	}
// 	free(tab);
// 	tab = NULL;
// }

void	ft_clean_token(t_token *token)
{
	free(token->string);
	free(token);
}

void	ft_clean_info_bis(t_info **info)
{
	if ((*info))
	{
		ft_lstclear(&(*info)->tokens, (void *)ft_clean_token);
		free((*info));
		*info = NULL;
	}
	//printf("t_info cleaned\n");
}

/* Fin */

t_info	*create_info(t_info *info)
{
	info = malloc(sizeof(t_info));
	if (!info)
		return (MEMORY_ERROR_PT); // la il faudra supprimer data
	ft_init_info(info);
	return (info);
}
