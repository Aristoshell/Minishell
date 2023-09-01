/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 00:09:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/01 20:05:37 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_sep(char c)
{
	if ((c >= 33 && c <= 126) || c == '|' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_printable(char c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
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

static int	countword(char const *s)
{
	int	i;
	int	counter;
	char quote = 0;
	bool quoote = false;
	bool op;

	i = 0;
	counter = 0;
	op = false;
	while (s[i])
	{
		while (is_printable(s[i]) == 0 && s[i] != 0)
			i++;
		if (is_printable(s[i]) == 1 && s[i] != 0)
		{
			quote = is_quote(s[i]);
			if (quote != 0)
			{
				quoote = true;
				counter++;
				printf("mot : |%s|\n", &s[i]);
				while (quoote || (!quoote && !is_sep(s[i + 1])))
				{
					if (is_quote(s[i]))
						quoote = false;
					i++;
				}
			}
			else if (is_op(s[i]) == true) // pour racourcir, envoyer pointer sur bool pour quil soit modif direct dans fonction
			{
				op = true;
				counter++;
				printf("mot : |%s|\n", &s[i]);
				i++;
			}
			else
			{
				counter++;
				printf("mot : |%s|\n", &s[i]);
				while(s[i] && is_printable(s[i]))
					i++;
			}
		}
	}
	printf("counter : %d\n", counter);
	return (counter);
}

static int	countlenword(char const *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (is_printable(s[i]) == 0 && s[i] != 0)
		i++;
	if (is_op(s[i]))
		return (1);
	char quote = is_quote(s[i]);
	if (quote != 0)
	{
		i++;
		count++;
		while (s[i] != quote)
		{
			i++;
			count++;
		}
		i++;
		count++;
	}
	else
	{
		while (is_printable(s[i]) == 1 && s[i] != 0 && is_op(s[i]) == 0)
		{
			i++;
			count++;
		}
	}
	return (count);
}

void	clear_split(char **split, int words)
{
	int	i;

	i = 0;
	while (i < words)
		free(split[i++]);
	free(split);
}
void fill_word(const char *str, char *word, int *i)
{
	int c;
	char quote;

	c = 0;
	quote = is_quote(str[*i]);
	if (is_op(str[*i]))
	{
		word[0] = str[*i];
		word[1] = 0;
		*i += 1;
		return;
	}
	if (quote != 0)
	{
		word[c] = str[*i];
		*i += 1;
		c++;
		while (str[*i] != quote)
		{
			word[c] = str[*i];
			c++;
			*i += 1;
		}
		word[c] = str[*i];
		*i += 1;
		c++;
	}
	else
	{	
		while (is_printable(str[*i]) == 1 && str[*i] != quote && is_op(str[*i]) == 0)
		{
			word[c] = str[*i];
			c++;
			*i += 1;
		}
	}
	word[c] = 0;
}

char	**ft_split_space(char const *str)
{
	char	**tab;
	int		words;
	int		nb_words;
	int		i;

	words = 0;
	i = 0;
	if (!str)
		return (NULL);
	nb_words = countword(str);
	tab = malloc((nb_words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (words < nb_words)
	{
		while (str[i] && is_printable(str[i]) == 0)
			i++;
		tab[words] = malloc((countlenword(&str[i]) + 1) * sizeof(char));
		if (!tab[words])
			return (clear_split(tab, words), NULL);
		fill_word(str, tab[words], &i);
		words++;
	}
	return (tab[words] = NULL, tab);
}
