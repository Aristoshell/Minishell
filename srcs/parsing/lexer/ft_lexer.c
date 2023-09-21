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

/* remplir le tableau de structure */
t_lexer_type	get_type(char *token)
{
	int	i;

	i = 0;
	if (token[i] == '|' && token[i + 1] == 0)
		return (type_pipe);
	else if (token[i] == '>' && token[i + 1] == 0)
		return (type_out);
	else if (token[i] == '>' && token[i + 1] == '>' && token[i + 2] == 0)
		return (type_append);
	else if (token[i] == '<' && token[i + 1] == 0)
		return (type_in);
	else if (token[i] == '<' && token[i + 1] == '<' && token[i + 2] == 0)
		return (type_heredoc);
	else
		return (type_word);
}

void	get_token_len_manage_quote(char c, bool	*in_quote, char *quote_type)
{
	if (ft_is_quote(c) && c == *quote_type)
	{
		*in_quote = false;
		*quote_type = 0;
	}
	else if (!(*in_quote) && ft_is_quote(c))
	{
		*in_quote = true;
		*quote_type = c;
	}
}

int	get_token_len(char *p, int *i)
{
	bool		in_quote;
	char		quote_type;
	int			len;

	in_quote = false;
	len = 0;
	quote_type = 0;
	if (!p[*i])
		return (*i += 1, 0);
	while (p[*i] && ft_is_space(p[*i]))
		*i += 1;
	if (ft_is_operator(p[*i]))
	{
		if ((p[*i] == '>' && p[*i+1] == '>') || (p[*i] == '<' && p[*i+1] == '<'))
			return (*i += 2, 2);
		return (*i += 1, 1);
	}
	while (p[*i] && (in_quote || (!in_quote && !ft_is_separator(p[*i]))))
	{
		get_token_len_manage_quote(p[*i], &in_quote, &quote_type);
		*i += 1;
		len++;
	}
	return (len);
}

void	fillword(char	*buffer, char *str, int size, int i)
{
	int	position;
	int	j;

	position = i - size;
	j = 0;
	while (j < size)
	{
		buffer[j] = str[position];
		j++;
		position++;
	}
	buffer[j] = 0;
}

char	*get_token(char *str, int *i)
{
	char	*word;
	int		size;

	size = get_token_len(str, i);
	if (size == 0)
		return (NULL);
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (MEMORY_ERROR_PT); // penser a free ce qui a ete malloc avant aussi
	fillword(word, str, size, *i);
	return (word);
}

int	ft_lexer(char const *str, t_info *info)
{
	int		i;
	int		j;

	if (!str)
		return (-1);
	info->nb_tokens = ft_countword(str);
	if (info->nb_tokens < 1)
		return (0);
	info->tokens = malloc(sizeof(t_token *) * info->nb_tokens);
	if (!info->tokens)
		return (MEMORY_ERROR_NB); // +free ce qui a ete free
	i = 0;
	j = 0;
	while (j < info->nb_tokens) //remplir le tableau de mots
	{
		info->tokens[j] = malloc(sizeof(t_token));
		if (!info->tokens[j])
			return (MEMORY_ERROR_NB); // + free ce qui a ete free
		info->tokens[j]->string = get_token((char *)str, &i);
		info->tokens[j]->type = get_type(info->tokens[j]->string);
		j++;
	}
	return (0);
}

/* main de vérif de fonctions 

int	main(void)
{
	char *str = ">grrrr omg<jpppp ohlala |< > 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'> <";
	int	nb_tokens;

	nb_tokens = ft_countword(str);
	printf("nb tokens : %d\n", nb_tokens);
	int i = 0;
	int size = -1;
	while (size)
	{
		size = get_token_len(str, &i);
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