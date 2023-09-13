/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/13 19:31:41 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../header/minishell.h"
#include <stdio.h>
#include <stdbool.h>

# define two_pipes (is_pipe(str[i]) && check)
# define first_is_pipe (is_pipe(str[i]) && !wrd)
# define last_is_pipe (!str[i] && check)

// checker les quotes ouvertes
// checker les pipes (interupteur et disjoncteur)
// checker les redirects

int	is_space(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

bool	is_pipe(char c)
{
	if (c == '|')
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

void	change_data_check_pipe(char c, bool	*check, bool *wrd)
{
	if (is_pipe(c))
		*check = true;
	else
		*check = false;
	if (!*wrd)
		*wrd = true;
}

void	check_pipe_quote(char *str, int *i)
{
	char	quote;

	while (str[*i])
	{
		quote = str[*i];
			*i += 1;
		while (str[*i] != quote)
			*i += 1;
		*i += 1;
		if (!is_quote(str[*i]))	
			return ;
	}
}

// gerer quand quote
int	check_pipe(char *str)
{
	int		i;
	bool	check;
	bool	wrd;

	i = -1;
	check = false;
	wrd = false;
	while (str[++i])
	{
		while (str[i] && is_space(str[i]) == 1)
			i++;
		if (two_pipes || first_is_pipe || last_is_pipe)
			return (printf("two_pipes : %d, first_is_pipe : %d, last_is_pipe : %d\n", two_pipes, first_is_pipe, last_is_pipe),false);
		if (is_quote(str[i]))
			check_pipe_quote(str, &i);
		if (str[i])
			change_data_check_pipe(str[i], &check, &wrd);
	}
	if (last_is_pipe)
		return (false);
	return (true);
}

int	check_redir(char *str)
{
	int	i = 0;
	int	to = 0;
	int	from = 0;
	int word = 0;
	while (str[i] && is_space(str[i]))
		i++;
	if (str[i] == '>')
		return (-2);
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '>')
			to++;
		else if (str[i] == '<')
			from++;
		else if (is_space(str[i]))
		{		
		}
		else
		{		
			to = 0;
			from = 0;
		}
		if (to > 2 || from > 2 || (to > 1 && from > 1))
			return (-1);
		if (word == 0)
			word = 1;
		i++;
	}
	if (to > 0 || from > 0)
		return (-3); // seul ou dernier
	return (0);
}
/*
Cas pas bons redirections
Pas de texte autour
"<" ok
" <"  ok
"< " ok
" < " ok
"<<"ok
" <<"ok
"<< "ok
" << "ok
">"
" >"
"> "
" > "
">>"
" >>"
">> "
" >> "

" cmd > > cmd "

debut et "> hihi"
debut et ">> hihi"
fin et "< hihi"
fin et "<<"
Attention espaces
*/

// int main(void)
// {
// 	char *test;
// 	test = "echo < < coucou";
// 	int rez = check_redir(test);
// 	printf("test : \"%s\" rez = %d\n", test, rez);
// 	return (0);
// }

int main(void)
{
	char *test;
	test = "| '||||' | cc|vv";
	int rez = check_pipe(test);
	printf("test : \"%s\" rez = %d\n", test, rez);
	return (0);
}
