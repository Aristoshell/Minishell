/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/08 11:17:01 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* fonctions qui renvoient des bool*/

bool	is_space(char c)
{
	if (c == 32 || c == 9)
		return (true);
	return (false);
}

char	is_quote(char c)
{
	if (c == '"')
		return ('"');
	if (c == '\'')
		return ('\'');
	return (0);
}

bool	is_op(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

bool	is_separator(char c)
{
	if (is_op(c) || is_space(c))
		return (true);
	return (false);
}


/* compte le nb de mots*/

void	count_word_manage_quote(char const *str, int *i)
{
	char	quote;
	
	quote = 0;
	while (str[*i] && (str[*i] == '\'' || str[*i] == '"'))
	{
		quote = str[*i];
		*i += 1;
		while (str[*i] && str[*i] != quote)
			*i += 1;
		*i += 1;
		if (is_space(str[*i]) == true)
			return ;
		if (is_op(str[*i]) == true)
			return;
		quote = str[*i];
	}
}

static int	countword(char const *str)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		while (str[i] && is_space(str[i]))
			i++;
		counter++;
		if (is_op(str[i]))
			i++;
		else
		{	
			while (str[i] && !is_space(str[i]) && !is_op(str[i]))
			{
				if (is_quote(str[i]))
					count_word_manage_quote(str, &i);
				else
					i++;
			}
		}
		while (str[i] && is_space(str[i]) == true)
			i++;
	}
	return (counter);
}

/* remplir le tableau de structure */
t_lexer_type	get_token(char *part)
{
	int	i;

	i = 0;
	if (part[i] == '|' && part[i + 1] == 0)
		return (token_pipe);
	else if (part[i] == '>' && part[i + 1] == 0)
		return (token_out);
	else if (part[i] == '<' && part[i + 1] == 0)
		return (token_in);
	else
		return (word);
}

void	get_part_len_manage_quote(char c, bool	*in_quote, char *quote_type)
{
	if (is_quote(c) && c == *quote_type)
	{
		*in_quote = false;
		*quote_type = 0;
	}
	else if (!(*in_quote) && is_quote(c))
	{
		*in_quote = true;
		*quote_type = c;
	}
}

int	get_part_len(char *p, int *i)
{
	bool		in_quote;
	char		quote_type;
	int			len;

	in_quote = false;
	len = 0;
	quote_type = 0;
	if (!p[*i])
		return (*i+=1, 0);
	while (p[*i] && is_space(p[*i]))
		*i+=1;
	if (is_op(p[*i]))
		return (*i+=1, 1);
	while (p[*i] && (in_quote || (!in_quote && !is_separator(p[*i]))))
	{
		get_part_len_manage_quote(p[*i], &in_quote, &quote_type);
		*i+=1;
		len++;
	}
	return (len);
}
void	fillword(char	*buffer, char *partition, int size, int i)
{
	int	position;
	int	j;
	
	position = i - size;
	j = 0;
	while (j < size)
	{
		buffer[j] = partition[position];
		j++;
		position++;
	}
	buffer[j] = 0;
}
char	*get_part(char *partition, int *i)
{
	char	*word;
	int		size;
	size = get_part_len(partition, i);
	if (size == 0)
		return (NULL);
	word = malloc(sizeof(char) * (size + 1));
	fillword(word, partition, size, *i);
	return (word);
}

/* fonction principale */
void	delete_t_parts(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_words)
	{
		if (info->words[i])
			free(info->words[i]);
		i++;
	}
	info->nb_words = 0;
	info->words = NULL;
}

int	ft_split_space(char const *str, t_info *info)
{
	int		i;
	int		j;
	
	if (!str)
		return (-1);
	j = 0;
	info->nb_words = countword(str);
	info->words = malloc(sizeof(t_parts *) * info->nb_words);
	if (!info->words)
		return (-2);
	i = 0;
	while (j < info->nb_words)
	{
		info->words[j] = malloc(sizeof(t_parts));
		if (!info->words[j])
			return (-2);
		info->words[j]->string = get_part((char *)str, &i);
		info->words[j]->token = get_token(info->words[j]->string);
		j++;
	}
	
	return(0);
}

/* main de vérif de fonctions 

int	main(void)
{
	char *str = ">grrrr omg<jpppp ohlala |< > 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'> <";
	int	nb_words;

	nb_words = countword(str);
	printf("nb words : %d\n", nb_words);
	int i = 0;
	int size = -1;
	while (size)
	{
		size = get_part_len(str, &i);
		printf("size = %d\n", size);
	}	
}
*/

// int	main(void)
// {
// 	char *str = ">grrrr omg<jpppp ohlala |< > 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'> <";
// 	t_info	info;
// 	ft_split_space(str, &info);
// 	int i = 0;
// 	printf("nb mots : %d\n", info.nb_words);
// 	while (i < info.nb_words)
// 	{
// 		printf("mot : %s, token : %d\n", info.words[i]->string, info.words[i]->token);
// 		i++;
// 	}
// }