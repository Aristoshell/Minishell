
#include "../../header/libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if ((str[i] == '-') || (str[i] == '+'))
		{
			if (str[i] == '-')
				sign = sign * -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9' )
		{
			nb = nb * 10 + str[i] - '0';
			i++;
		}
		return (nb * sign);
	}
	return (0);
}
