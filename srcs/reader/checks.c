/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/12 17:01:28 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../header/minishell.h"
#include <stdio.h>

// checker les quotes ouvertes
// checker les pipes (interupteur et disjoncteur)
// checker les redirects

int	is_space(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}
// gerer quand quote
int	check_pipe(char *str)
{
	int	i;
	int	check;
	int	word;

	i = -1;
	check = 0;
	word = 0;
	while (str[++i])
	{
		while (str[i] && is_space(str[i]) == 1)
			i++;
		if (str[i] == '|' && (check == 1 || word == 0 || str[i] == 0))
			return (-1);
		if ((str[i] == 0 && check == 1))
			return (-1);
		if (str[i] == '|')
			check = 1;
		else
			check = 0;
		if (word == 0)
			word = 1;
	}
	if (check == 1)
		return (-1);
	return (0);
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

int main(void)
{
	char *test;
	test = "echo < < coucou";
	int rez = check_redir(test);
	printf("test : \"%s\" rez = %d\n", test, rez);
	return (0);
}

// int main(void)
// {
// 	char *test;
// 	test = "echo '||' coucou";
// 	int rez = check_pipe(test);
// 	printf("test : \"%s\" rez = %d\n", test, rez);
// 	return (0);
// }
