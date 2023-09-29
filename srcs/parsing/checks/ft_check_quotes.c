
#include "minishell.h"
#include "minishell_louis.h"

char	check_open_quote(const char *input)
{
	int		i;
	char	delimiter;

	i = 0;
	delimiter = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE || input[i] == SIMPLE_QUOTE)
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


//utilise avant mais pas besoin, fonction a garder pour plus tard maybe
// int	ft_srch_char(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == (unsigned char) c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// char	*ft_join_tmp(char *end_of_input, char *additional_line, char	*tmp)
// {
// 	if (end_of_input)
// 	{
// 		tmp = ft_strjoin(end_of_input, additional_line);
// 		free(end_of_input);
// 	}
// 	else
// 		tmp = strdup(additional_line);
// 	free(additional_line);
// 	return (tmp);
// }

// char	*close_quote(const char quote)
// {
// 	char	*end_of_input;
// 	char	*additional_line;
// 	char	*tmp;

// 	write(1, ">", 1);
// 	end_of_input = NULL;
// 	additional_line = ft_get_next_line(0);
// 	tmp = NULL;
// 	while (ft_srch_char(additional_line, quote) == 0)
// 	{
// 		tmp = ft_join_tmp(end_of_input, additional_line, tmp);
// 		end_of_input = ft_strdup(tmp);
// 		free(tmp);
// 		write(1, ">", 1);
// 		additional_line = ft_get_next_line(0);
// 	}
// 	tmp = ft_join_tmp(end_of_input, additional_line, tmp);
// 	tmp[strlen(tmp) - 1] = 0;
// 	return (tmp);
// }

// char	*manage_quote(char *input)
// {
// 	char	quote;
// 	char	*tmp;
// 	char	*end_ofquote;

// 	quote = 0;
// 	tmp = NULL;
// 	end_ofquote = NULL;
// 	quote = check_open_quote(input);
// 	while (quote != 0)
// 	{
// 		end_ofquote = close_quote(quote);
// 		tmp = ft_strdup(input);
// 		free(input);
// 		input = ft_strjoin(tmp, end_ofquote);
// 		free(end_ofquote);
// 		free(tmp);
// 		quote = check_open_quote(input);
// 	}
// 	return (input);
// }
