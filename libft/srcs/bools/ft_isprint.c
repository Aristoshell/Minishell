
#include "../../header/libft.h"

int	ft_isprint(int i)
{
	if ((i >= 32 && i <= 126))
		return (1);
	return (0);
}
