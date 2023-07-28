/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madavid <madavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:29:29 by marine            #+#    #+#             */
/*   Updated: 2023/07/28 11:53:35 by madavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_srch_char(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (1);
		i++;
	}
	return (0);
}

char *close_quote(char quote)
{
	char	*end_of_input;
	char	*additional_line;
	char	*tmp;
	
	write(1, ">", 1);
	end_of_input = NULL;
	additional_line = ft_get_next_line(0);
	while (ft_srch_char(additional_line, quote) == 0)
	{
		if (end_of_input)
		{
			tmp = ft_strjoin(end_of_input, additional_line);
			free(end_of_input);
		}
		else
			tmp = strdup(additional_line);
		free(additional_line);
		end_of_input = ft_strdup(tmp);
		free(tmp);
		write(1, ">", 1);
		additional_line = ft_get_next_line(0);
	}
	if (end_of_input == NULL)
		tmp = strdup(additional_line);
	else
	{
		tmp = ft_strjoin(end_of_input, additional_line);
		free(end_of_input);	
	}
	int size = strlen(tmp);
	tmp[size - 1] = 0;
	free(additional_line);
	return (tmp);
}

char	check_open_quote(char *input)
{
	int		i;
	char	delimiter;

	i = 0;
	delimiter = 0;
	while (input[i])
	{
		if (input[i] == double_quote || input[i] == simple_quote)
		{
			delimiter = input[i];
			i++;
			while (input[i] && delimiter != 0)
			{
				if (input[i++] == delimiter)
					delimiter = 0;
			}
			if (!input[i] && delimiter != 0)
				return (delimiter);
		}
		else
			i++;
	}
	return (delimiter);
}

// int main(void)
// {
// 	printf("Doit afficher 1 : %c\n", check_open_quote("\"Coucou\" \"hihi\" \" dddd "));
// 	//printf("Doit afficher 0 : %c\n", check_open_quote("Coucou  \'hihi\'"));

// 	return(1);
// }
