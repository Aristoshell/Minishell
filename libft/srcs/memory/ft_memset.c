
#include "../../header/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	long unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
