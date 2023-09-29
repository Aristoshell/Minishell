/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/21 15:02:13 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_louis.h"

int	ft_fill_token_table(const char *input, t_info *info)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < info->nb_tokens) //remplir le tableau de mots
	{
		info->tokens[j] = malloc(sizeof(t_token));
		if (!info->tokens[j])
			return (MEMORY_ERROR_NB); // + free ce qui a ete free
		info->tokens[j]->string = get_token_val(input, &i);
		info->tokens[j]->type = get_token_type(info->tokens[j]->string);
		j++;
	}
	return (FUNCTION_SUCCESS);
}

int	ft_lexer(const char *input, t_info *info)
{
	if (!input)
		return (-1);
	info->nb_tokens = ft_count_token(input);
	if (info->nb_tokens < 1)
		return (0); //voir ce quil se passe si je retourne ca, normalement cest pas censee, mais si je retourne un val je dois bien gerer dans la fonction davant
	info->tokens = malloc(sizeof(t_token *) * info->nb_tokens);
	if (!info->tokens)
		return (MEMORY_ERROR_NB); // +free ce qui a ete free
	if (ft_fill_token_table(input, info) == MEMORY_ERROR_NB)
		return (MEMORY_ERROR_NB); //attention a bien free ce quil faut
	return (FUNCTION_SUCCESS);
}

/* main de vérif de fonctions 

int	main(void)
{
	char *str = ">grrrr omg<jpppp ohlala |< > 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'> <";
	int	nb_tokens;

	nb_tokens = ft_count_token(str);
	printf("nb tokens : %d\n", nb_tokens);
	int i = 0;
	int size = -1;
	while (size)
	{
		size = ft_get_token_val_len(str, &i);
		printf("size = %d\n", size);
	}	
}
*/

// int	main(void)
// {
// 	char *str = ">grrrr omg<jpppp ohlala |< > 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'> <";
// 	t_info	info;
// 	lexer(str, &info);
// 	int i = 0;
// 	printf("nb mots : %d\n", info.nb_tokens);
// 	while (i < info.nb_tokens)
// 	{
// 		printf("mot : %s, type : %d\n", info.tokens[i]->string, info.tokens[i]->type);
// 		i++;
// 	}
// }