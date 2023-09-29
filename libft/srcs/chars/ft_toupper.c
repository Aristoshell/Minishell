
#include "../../header/libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{	
		c -= 32;
		return (c);
	}
	else
		return (c);
}
