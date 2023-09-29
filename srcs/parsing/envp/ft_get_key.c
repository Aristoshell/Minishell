
#include "minishell.h"
#include "minishell_louis.h"

char	*ft_get_key(char *line, int sep)
{
	char	*key;
	int		size;

	if (sep < 0)
		size = ft_strlen(line);
	else
		size = sep;
	key = malloc((size + 1) * sizeof(char));
	if (!key)
		return (MEMORY_ERROR_PT);// attention a l'erreur renvoyee
	ft_strlcpy(key, line, (size + 1));
	return (key);
}
