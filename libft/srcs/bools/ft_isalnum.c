
#include "../../header/libft.h"

int	ft_isalnum(int i)
{
	if (ft_isdigit(i) != 0 || ft_isalpha(i) != 0)
		return (1);
	return (0);
}
