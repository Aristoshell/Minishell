/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/14 13:31:24 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

// checker les redirects

bool	check_start(char *str, int *i)
{
	while (str[*i] && is_space(str[*i]))
		*i += 1;
	if (is_quote(str[*i]))
		pass_when_quote(str, i);
	if (str[*i] == '>')
		return (false);
	return (true);
}
// printf("ici\n")


bool	check_redir_to(char *str, int *i)
{
	*i += 1;
	if (str[*i] == '>')
		*i += 1;
	while (str[*i] && is_space(str[*i]))
		*i += 1;
	if (str[*i] == '<')
		return (false);
	if (is_quote(str[*i]))
		pass_when_quote(str, i);
	else if (!str[*i] || str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
		return (false);
	return (true);
}

bool	check_redir_from(char *str, int *i)
{
	*i += 1;
	if (str[*i] == '<')
		*i += 1;
	while (str[*i] && is_space(str[*i]))
		*i += 1;
	if (str[*i] == '<')
		return (false);
	if (is_quote(str[*i]))
		pass_when_quote(str, i);
	else if (!str[*i] || str[*i] == '|' || str[*i] == '>' || str[*i] == '<')
		return (false);
	return (true);
}

bool	check_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!i && !check_start(str, &i))
			return (printf("check start\n"), false);
		if (str[i] == '<')
			if (!check_redir_from(str, &i))
				return (printf("check redir from\n"), false);
		else if (str[i] == '>')
			if (!check_redir_to(str, &i))
				return (printf("check redir to\n"), false);
		else
			i++;
	}
	return (true); // check si pas conditions avant
}

// int	check_redir(char *str)
// {
// 	int	i = 0;
// 	int	to = 0;
// 	int	from = 0;
// 	int word = 0;
// 	while (str[i] && is_space(str[i]))
// 		i++;
// 	if (str[i] == '>')
// 		return (-2);
// 	while (str[i])
// 	{
// 		if (str[i] == '>' && str[i + 1] == '>')
// 			to++;
// 		else if (str[i] == '<')
// 			from++;
// 		else if (is_space(str[i]))
// 		{		
// 		}
// 		else
// 		{		
// 			to = 0;
// 			from = 0;
// 		}
// 		if (to > 2 || from > 2 || (to > 1 && from > 1))
// 			return (-1);
// 		if (word == 0)
// 			word = 1;
// 		i++;
// 	}
// 	if (to > 0 || from > 0)
// 		return (-3); // seul ou dernier
// 	return (0);
// }
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
">" ok
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


// quand on est dans des quotes
// ca check pas quand dernier est op mais quapres on na que des espaces
// check pas si trois quotes i guess
// attention aux <> et ><

int main(void)
{
	char *test;
	test = "< hihi >< Makefile cat | grep \".c\"";
	int rez = check_redir(test);
	printf("test : \"%s\" rez = %d\n", test, rez);
	return (0);
}

// a traiter now ; dans redirect from :
// - si <<< (+de 2)
// - si < < 