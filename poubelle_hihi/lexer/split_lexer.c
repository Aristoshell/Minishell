/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:47:29 by marine            #+#    #+#             */
/*   Updated: 2023/08/08 19:33:19 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_printable(char c)
{
	if (c >= 33 && c <= 127)
		return (1);
	return (0);
}

bool	is_meta(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}


int	countwordlenquote(char const *str, int *i, char quote)
{
	int		len_word;

	len_word = 0;
	while(str[*i] && str[*i] != quote) // ici futur probleme pour la gestion des quotes car le meta est important si quote
	{
		*i += 1 ;
		len_word++;
	}
	return (len_word);
}

int	countwordlen(char const *str, int *i)
{
	int		len_word;

	len_word = 0;
	while(str[*i] && is_printable(str[*i]) == 1 && is_meta(str[*i]) == false && is_quote(str[*i]) == false) // ici futur probleme pour la gestion des quotes car le meta est important si quote
	{
		*i += 1 ;
		len_word++;
	}
	return (len_word);
}

char	*malloc_meta(char const *str, int *i)
{
	char	*word;

	word = malloc (sizeof(char) * 2);
	if (word == NULL)
		return (NULL);
	word[0] = str[*i];
	word[1] = 0;
	*i += 1;
	return(word);
}

char	*malloc_quote(char const *str, int *i)
{
	char	quote;
	char	*word;
	int				len_word;
	int j;

	j = 0;
	quote = str[*i];
	len_word = 0;
	*i += 1;
	len_word = countwordlenquote(str, i, quote); // compter taille mot
	*i = *i - len_word;
	word = malloc((len_word + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j < len_word)
	{
		word[j] = str[*i];
		j++;
		*i += 1;
	}
	word[len_word] = 0;
	if (str[*i] == quote)
		*i += 1;
	return(word);
}


char	*ft_split_lexer(char const *str, int *i)
{
	char			*word;
	int				len_word;
	//t_open_quote	open_quote;
	int				j;
	len_word = 0;
	//open_quote = no;
	j = 0;
	if (!str)
	return (NULL);
	while (str[*i] && is_printable(str[*i]) == 0) // sauter les espaces
		*i = *i + 1;
	if (is_meta(str[*i]) == true) // check si meta
		return (malloc_meta(str, i));
	if (is_quote(str[*i]) == true) // check si meta
		return (malloc_quote(str, i));
	len_word = countwordlen(str, i); // compter taille mot
	*i = *i - len_word;
	word = malloc((len_word + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (j < len_word)
	{
		word[j] = str[*i];
		j++;
		*i += 1;
	}
	word[len_word] = 0;
	return (word);
}


/* 

Vérifications à faire

- si on est dans une quote, ne pas prendre en compte les metas characteres
- tant qu'une quote n'est pas fermée, on n'a pas fini le len word 
- vérifier si on a des \
*/