
#include "minishell.h"
#include "minishell_louis.h"

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
		if (ft_is_space(str[*i]) == true)
			return ;
		if (ft_is_operator(str[*i]) == true)
			return ;
		quote = str[*i];
	}
}
void	check_kind(char *str, int *i)
{
	if (ft_is_operator(str[*i]))
	{
		if ((str[*i] == '>' && str[(*i) + 1] == '>') || (str[*i] == '<' && str[(*i) + 1] == '<'))
			*i += 1;
		*i += 1;
	}
	else
	{
		while (str[*i] && !ft_is_space(str[*i]) && !ft_is_operator(str[*i]))
		{
			if (ft_is_quote(str[*i]))
				count_word_manage_quote(str, i);
			else
				*i += 1;
		}
	}
}

int	ft_count_token(char const *str)
{
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	if (!str[i])
		return (0);
	while (str[i])
	{
		while (str[i] && ft_is_space(str[i]))
			i++;
		if (!str[i])
			return (counter);
		counter++;
		check_kind((char *)str, &i);
		while (str[i] && ft_is_space(str[i]) == true)
			i++;
	}
	return (counter);
}
