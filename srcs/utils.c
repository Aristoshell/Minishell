
#include "minishell.h"
#include "minishell_louis.h"

void	ft_free_2d_array(char **two_di_array)
{
	int	i;

	i = 0;
	if (two_di_array)
	{
		while (two_di_array[i])
		{
			free(two_di_array[i]);
			two_di_array[i] = NULL;
			i++;
		}
		free(two_di_array);
		two_di_array = NULL;
	}
}
