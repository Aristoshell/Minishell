#include "../../libft/header/libft.h"

int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		char	*str1;
		char	*str2;
		int		rez;
		int		len;

		str1 = argv[1];
		str2 = argv[2];
		if (ft_strlen(str1) > ft_strlen(str2))
			len = ft_strlen(str1);
		else
			len = ft_strlen(str2);
		rez = ft_strncmp(str1, str2, len);
		printf("rez = %d\n", rez);
	}
	return (0);
}
