
#include "../../header/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	while (i <= size)
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
