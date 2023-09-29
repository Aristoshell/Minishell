
#include "../../header/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;

	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, ft_strlen(s) + 1);
	return (dest);
}
