
#include "../../header/libft.h"

char	*get_hex_value_min(unsigned long nbr, int *size)
{
	char	*str;

	if (nbr == 0)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '0';
		*size += 1;
		return (str);
	}
	str = ft_itoa_hex(nbr, HEXA_VAL_MIN);
	*size += ft_strlen(str);
	return (str);
}

char	*get_hex_value(unsigned long nbr, int *size)
{
	char	*str;

	if (nbr == 0)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '0';
		*size += 1;
		return (str);
	}
	str = ft_itoa_hex(nbr, HEXA_VAL);
	*size += ft_strlen(str);
	return (str);
}
