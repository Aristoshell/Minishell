
#include "minishell.h"
#include "minishell_louis.h"

void	ft_clean_2d_array(void **array, void (*clean_data)(void *))
{
	const unsigned long int	size = sizeof(array);
	unsigned long int		i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
	{
		if (array[i])
			clean_data(&array[i]);
		i++;
	}
	free(array);
}
