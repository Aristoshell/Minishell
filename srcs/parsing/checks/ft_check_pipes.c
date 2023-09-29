
#include "minishell.h"
#include "minishell_louis.h"

void	change_data_check_pipe(char c, bool	*check, bool *wrd)
{
	if (ft_is_pipe(c))
		*check = true;
	else
		*check = false;
	if (!*wrd)
		*wrd = true;
}

bool	check(char c, bool pipe, bool word)
{
	bool	two_pipes;
	bool	first_ft_is_pipe;
	bool	last_ft_is_pipe;

	two_pipes = (ft_is_pipe(c) && pipe);
	first_ft_is_pipe = (ft_is_pipe(c) && !word);
	last_ft_is_pipe = (!c && pipe);
	if (two_pipes || first_ft_is_pipe || last_ft_is_pipe)
		return (false);
	return (true);
}

bool	check_pipe(const char *str)
{
	int		i;
	bool	pipe;
	bool	wrd;

	i = -1;
	pipe = false;
	wrd = false;
	while (str[++i]) //pb ici
	{
		while (str[i] && ft_is_space(str[i]) == 1)
			i++;
		if (!check(str[i], pipe, wrd))
			return (true);
		if (ft_is_quote(str[i]))
			ft_pass_when_quote(str, &i);
		if (str[i])
			change_data_check_pipe(str[i], &pipe, &wrd);
	}
	if (!str[i] && pipe)
		return (true);
	return (false);
}
