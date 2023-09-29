
#include "../../header/libft.h"

void	ft_args_pf(int output, char c, va_list ap, int *n)
{
	if (c == 'c')
		return (ft_putchar_pf(output, va_arg(ap, int), n));
	if (c == 's' )
		return (ft_putstr_pf(output, va_arg(ap, char *), n));
	if (c == 'p')
		return (ft_putptr_pf(output, va_arg(ap, unsigned long int), n));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_pf(output, va_arg(ap, int), n, 0));
	if (c == 'u')
		return (ft_putnbr_pf(output, va_arg(ap, unsigned int), n, 1));
	if (c == 'x')
		return (ft_puthexa_pf(output, va_arg(ap, unsigned int), n, 0));
	if (c == 'X')
		return (ft_puthexa_pf(output, va_arg(ap, unsigned int), n, 1));
	return ;
}

int	ft_printf(int output, const char *str, ...)
{
	int		i;
	int		n;
	va_list	ap;

	if (!str)
		return (-1);
	i = 0;
	n = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] != '%')
			ft_putchar_pf(output, str[i++], &n);
		else
		{
			if (str[i] == '%' && str[i + 1] == '%')
				ft_putchar_pf(output, str[i], &n);
			else
				ft_args_pf(output, str[i + 1], ap, &n);
			i += 2;
		}
	}
	va_end(ap);
	return (n);
}
