/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_split_spaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marine <marine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/06 14:49:08 by marine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdbool.h>
#include <stdlib.h>

# define double_quote 34
# define simple_quote 39
 
typedef enum e_lexer_type
{
	word,
	token_pipe,
	token_in,
	token_out
}			t_lexer_type;

typedef struct s_parts
{
	char			*string;
	t_lexer_type	token;
}			t_parts;


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
int	count_quote(char const *str, int *i)
{
	char	quote;
	
	quote = 0;
	int	count;
	count = 0;
	while (str[*i] && (str[*i] == '\'' || str[*i] == '"'))
	{
		quote = str[*i];
		*i += 1;
		while (str[*i] && str[*i] != quote)
		{
			*i += 1;
			count++;
		}
		*i += 1;
		count++;
		if (is_space(str[*i]) == true)
			return (printf("str[%d] : %c (%d), taille mot : %d\n", *i, str[*i], str[*i], count), count);
		if (is_op(str[*i]) == true)
			return (printf("str[%d] : %c (%d), taille mot : %d\n", *i, str[*i], str[*i], count), count);
		quote = str[*i];
	}
	return (printf("str[%d] : %c (%d), taille mot : %d\n", *i, str[*i], str[*i], count), count);
}

void	manage_quote(char const *str, int *i)
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


// static int	countword(char const *str)
// {
// 	int		counter;
// 	int		i;

// 	counter = 0;
// 	i = 0;
// 	if (!str[i])
// 		return (0);
// 	while (str[i])
// 	{
// 		while (str[i] && is_space(str[i]))
// 			i++;
// 		printf("str[%d] : %c (%d)\n", i, str[i], str[i]);
// 		counter++;
// 		if (is_op(str[i]))
// 			i++;
// 		else
// 		{	
// 			while (str[i] && !is_space(str[i]) && !is_op(str[i]))
// 			{
// 				if (is_quote(str[i]))
// 					manage_quote(str, &i);
// 				else
// 					i++;
// 			}
// 		}
// 		while (str[i] && is_space(str[i]) == true)
// 			i++;
// 	}
// 	return (counter);
// }

// int	*countlenword(char const *str, int nb_words)
// {
// 	int	word;
// 	int	i;

// 	word = 0;
// 	i = 0;
// 	int	*tab;

// 	if (!str[i])
// 		return (NULL);
// 	tab = malloc(nb_words);
// 	while (str[i])
// 	{
// 		while (str[i] && is_space(str[i]))
// 			i++;
// 		if (is_op(str[i]))
// 		{
// 			i++;
// 			tab[word] = 1;
// 		}
// 		else
// 		{	
// 			tab[word] = 0;
// 			while (str[i] && !is_space(str[i]) && !is_op(str[i]))
// 			{
// 				if (is_quote(str[i]))
// 				{
// 					tab[word] = count_quote(str, &i);
// 					break;
// 				}
// 				else
// 				{
// 					tab[word]++;
// 					i++;
// 				}
// 			}
// 		}
// 		word++;

// 	}
// 	return (tab);
// }

typedef enum e_open_quote
{
	no_q,
	simple_q,
	double_q
}			t_open_quote;

int	get_part_len(char *p)
{
	int			i;
	bool		in_quote;
	char		quote_type;
	int			len;

	i = 0;
	in_quote = false;
	len = 0;
	quote_type = 0;
	while (p[i] && is_space(p[i]))
		i++;
	if (!p[i])
		return(0);
	if (is_op(p[i]))
		return (1);
	while (p[i] && (in_quote || (!in_quote && !is_separator(p[i]))))
	{
		if (is_quote(p[i]) && p[i] == quote_type)
		{
			in_quote = false;
			quote_type = 0;
		}
		else if (!in_quote && is_quote(p[i]))
		{
			in_quote = true;
			quote_type = p[i];
		}
		i++;
		len++;
	}
	return (len);
}
int main(void)
{
	int	size;

	size = get_part_len("|");
	printf("size : %d\n", size);
}
/*
void	clear_split(char **split, int words)
{
	int	i;

	i = 0;
	while (i < words)
		free(split[i++]);
	free(split);
}
*/

// void fill_word(const char *str, char *word, int *i)
// {
// 	int c;
// 	char quote;

// 	c = 0;
// 	quote = is_quote(str[*i]);
// 	if (is_op(str[*i]))
// 	{
// 		word[0] = str[*i];
// 		word[1] = 0;
// 		*i += 1;
// 		return;
// 	}
// 	if (quote != 0)
// 	{
// 		*i += 1;
// 		while (str[*i] != quote)
// 		{
// 			word[c] = str[*i];
// 			c++;
// 			*i += 1;
// 		}
// 		*i += 1;
// 	}
// 	else
// 	{	
// 		while (is_printable(str[*i]) == 1 && str[*i] != quote && is_op(str[*i]) == 0)
// 		{
// 			word[c] = str[*i];
// 			c++;
// 			*i += 1;
// 		}
// 	}
// 	word[c] = 0;
// 	//printf("\033[98mword : \033[0m%s\n", word);
// }


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

char	*get_part(char *partition)
{
	char	*word;
	int		size;

	size = get_part_len(partition);
	word = malloc(sizeof(char) * (size + 1));
	fillword(word);
	return (word);
}

char	**ft_split_space(char const *str)
{
	//char	**tab;
	//int		words;
	int		nb_words;
	//int		i;

	//words = 0;
	//i = 0;
	if (!str)
		return (NULL);
	nb_words = countword(str);
 	printf("nb words : %d\n", nb_words);
	int *tab;
	tab = countlenword(str, nb_words);
	int grr = 0;
	while (grr < nb_words)
	{
		printf("size word[%d] : %d\n", grr, tab[grr]);
		grr++;
	}
	t_parts *partition[nb_words];
	while (grr < nb_words)
	{
		partition[grr] = malloc(sizeof(t_parts));
		partition[grr]->string = get_part; //fonction à coder pour fill la string
		partition[grr]->token = get_token(partition[grr]->string);
		grr++;
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
	return(NULL);
}

int main(void)
{
	char **new;

	//new = ft_split_space("coucou   '\"|\"' hihiihihi 'grrrr|>hihi' | ><| | < >'bouhiuu hfdgh dsfk'   grrr");
	new = ft_split_space("	omg 'ntm>'|echo'lol' > \"bjr|ahah | hihi\"  coucou jpp putain| |||  | |>");
	// new = ft_split_space("\"lol                                 bonjour\"lal\"lil\"");
	(void) new;
	// int i = 0;
	// while (new[i])
	// {
	// 	printf("new[i] = %s\n", new[i]);
	// 	i++;
	// }
}

