
#include "../../header/libft.h"

int	ft_strchr_int(const char *s, int c)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(s);
	while (i <= size)
	{
		if (s[i] == (unsigned char) c)
			return (i);
		i++;
	}
	return (-1);
}
