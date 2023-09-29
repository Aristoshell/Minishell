
#include "../../header/libft.h"

int	calc_char(unsigned int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa_u(unsigned int n)
{
	char	*final;

	final = malloc((calc_char(n) + 1) * sizeof(char));
	if (!final)
		return (NULL);
	final[calc_char(n)] = '\0';
	while (n > 9)
	{
		final[calc_char(n) - 1] = n % 10 + '0';
		n = n / 10;
	}
	final[0] = n + '0';
	return (final);
}
