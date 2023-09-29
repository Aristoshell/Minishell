
#include "../../header/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	//printf("%s (%lu), %s(%lu)\n", s1, strlen(s1), s2, strlen(s2));
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	//printf("%d\n", (unsigned char)s1[i] - (unsigned char)s2[i]);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
