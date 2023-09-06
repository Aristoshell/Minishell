/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/06 16:56:24 by marine           ###   ########.fr       */
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

int	get_part_len( char *p, int *i)
{
	bool		in_quote;
	char		quote_type;
	int			len;

	in_quote = false;
	len = 0;
	quote_type = 0;
	while (p[*i] && is_space(p[*i]))
		*i+=1;
	if (!p[*i])
		return (*i+=1, 0);
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

char	*get_part(char *partition, int *i)
{
	char	*word;
	int		size;
	printf("recu : %s, %d\n", partition, *i);
	size = get_part_len(&partition[*i], i);
	word = malloc(sizeof(char) * (size + 1));
	printf("size : %d\n", size);
	//fillword(word);
	return (word);
}

/* fonction principale */

t_parts	**ft_split_space(char const *str)
{
	int		nb_words;
	t_parts **partition;
	int		j;
	int		i;
	
	if (!str)
		return (NULL); // comment faire la diff avec mauvais malloc et juste str vide ? en vrai normalement si la str est vide ca aura été géré avant hihi (mais à check quand même)
	j = 0;
	nb_words = countword(str);
	partition = malloc(sizeof(t_parts *) * nb_words);
	if (!partition)
		return (NULL);
	while (j < nb_words)
	{
		i = 0;
		partition[j] = malloc(sizeof(t_parts));
		if (!partition[j])
			return (NULL); // et supprime aussi celles d'avant
		partition[j]->string = get_part((char *)str, &i); //fonction à coder pour fill la string
		// //partition[j]->token = get_token(partition[j]->string);
		// //printf("tab[%d] = %c, token = %d\n", j, str[i], partition[j]->token);
		j++;
	}
	// tab = malloc((nb_words + 1) * sizeof(char *));
	// if (!tab)
	// 	return (NULL);
	// while (words < nb_words)
	// {
	// 	while (str[i] && is_printable(str[i]) == 0)
	// 		i++;
	// 	tab[words] = malloc((countlenword(&str[i]) + 1) * sizeof(char));
	// 	if (!tab[words])
	// 		return (clear_split(tab, words), NULL);
	// 	fill_word(str, tab[words], &i);
	// 	words++;
	// }
	//return (tab[words] = NULL, tab);
	return(partition);
}

/* main de vérif de fonctions 

int	main(void)
{
	char *str = "grrrr omg jpppp ohlala 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'";
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

int	main(void)
{
	char *str = "grrrr omg jpppp ohlala 'putain|de|merde hihi cest encore la meme quote'\"encore la aussi\"|mais plus maintenant hihi |'grr'";
	//int	nb_words;

	ft_split_space(str);
}