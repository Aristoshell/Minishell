
#include "../../header/libft.h"

char	*str_reverse(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str) + 1);
	new[ft_strlen(str)] = 0;
	while (str[i])
	{
		new[i] = str[ft_strlen(str) - 1 - i];
		i++;
	}
	new[i] = '\0';
	return (free(str), new);
}

char	*ft_intohex(char *str, unsigned long nbr, char *base_to)
{
	int	i;

	i = 0;
	while (nbr > 0)
	{
		str[i] = base_to[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	if (nbr != 0)
	{
		str[i] = base_to[nbr % 16];
		i++;
	}
	str[i] = '\0';
	str = str_reverse(str);
	return (str);
}

char	*ft_itoa_hex(unsigned long nbr, char *base_to)
{
	char	*str;

	str = ft_calloc(34, sizeof(char));
	str = ft_intohex(str, nbr, base_to);
	return (str);
}
