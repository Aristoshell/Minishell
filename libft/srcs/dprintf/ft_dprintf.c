
#include "../../header/libft.h"

int	is_convert(char c)
{
	char	*convert;
	int		i;

	convert = "cspdiuxX%";
	i = 0;
	while (i < 9)
	{
		if (c == convert[i])
			return (1);
		i++;
	}
	return (0);
}

char	*get_percent(int *size)
{
	*size += 1;
	return (ft_strdup("%"));
}

char	*arg_to_content(char c, va_list args, int *size)
{
	if (c == 'c')
		return (get_char((va_arg(args, int)), size));
	if (c == 's')
		return (get_string((va_arg(args, char *)), size));
	if (c == 'p')
		return (get_pointer(va_arg(args, unsigned long), size));
	if (c == 'd')
		return (get_int(va_arg(args, int), size));
	if (c == 'i')
		return (get_int(va_arg(args, int), size));
	if (c == 'u')
		return (get_unsigned_int(va_arg(args, unsigned int), size));
	if (c == 'x')
		return (get_hex_value_min(va_arg(args, unsigned int), size));
	if (c == 'X')
		return (get_hex_value(va_arg(args, unsigned int), size));
	if (c == '%')
		return (get_percent(size));
	return (NULL);
}

int	ft_dprintf(int fd, char	*str, ...)
{
	char		*new_str;
	int			size;
	va_list		args;

	if (!str)
		return (-1);
	new_str = NULL;
	size = 0;
	va_start(args, str);
	new_str = fill_new(str, args, &size);
	va_end(args);
	write(fd, new_str, size);
	free(new_str);
	return (size);
}
