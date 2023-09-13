/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:42:19 by madavid           #+#    #+#             */
/*   Updated: 2023/09/13 20:33:44 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>

# define two_pipes (is_pipe(str[i]) && check)
# define first_is_pipe (is_pipe(str[i]) && !wrd)
# define last_is_pipe (!str[i] && check)

// checker les quotes ouvertes
// checker les pipes (interupteur et disjoncteur)
// checker les redirects

bool	is_pipe(char c)
{
	if (c == '|')
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
		if (two_pipes || first_is_pipe || last_is_pipe) // faire une fonction avec des bits
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

int main(void)
{
	char *test;
	test = "| '||||' | cc|vv";
	int rez = check_pipe(test);
	printf("test : \"%s\" rez = %d\n", test, rez);
	return (0);
}


