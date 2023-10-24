
#include "minishell.h"
#include "minishell_louis.h"

char	*ft_get_val(char *line)
{
	char	*val;
	int		size;

	size = ft_strlen(line);
	val = malloc((size + 1) * sizeof(char));
	if (!val)
		return (MEMORY_ERROR_PT);
	if (!size)
		val[0] = 0;
	else
		ft_strlcpy(val, line, (size + 1)); //attention au retour de cette fonction ?
	return (val);
}
