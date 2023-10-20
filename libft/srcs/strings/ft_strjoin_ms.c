
#include "../../header/libft.h"

char	*ft_strjoin_ms(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*s_new;

	i = 0;
	j = 0;
	// if (!s1 && !s2)
	// 	return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s_new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s_new == NULL)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		s_new[i] = s1[i];
		i++;
	}
	while (j < ft_strlen(s2))
	{
		s_new[i] = s2[j];
		i++;
		j++;
	}
	return (s_new[i] = 0, s_new);
}
