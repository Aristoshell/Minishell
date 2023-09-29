
#include "../../header/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*big_;

	i = 0;
	big_ = (char *)big;
	if (ft_strlen(little) > len)
		return (NULL);
	if (ft_strlen(little) == 0)
		return (big_);
	while (i <= len - ft_strlen(little) && big_[i])
	{
		if (ft_strncmp(&big_[i], little, ft_strlen(little)) == 0)
			return (&big_[i]);
		i++;
	}
	return (NULL);
}
