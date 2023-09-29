
#include "../../header/libft.h"

void	ft_putchar_pf(int output, char c, int *n)
{
	write(output, &c, 1);
	*n += 1;
}

void	ft_putstr_pf(int output, char *str, int *n)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr_pf(output, "(null)", n);
		return ;
	}
	while (str[i])
		write(output, &str[i++], 1);
	*n = *n + i;
}

void	ft_putnbr_pf(int output, long long int nb, int *n, int is_unsigned)
{
	if (!is_unsigned && nb < 0)
	{
		ft_putchar_pf(output, '-', n);
		nb *= -1;
	}
	if (nb <= 9)
	{
		ft_putchar_pf(output, nb + '0', n);
	}
	if (nb > 9)
	{
		ft_putnbr_pf(output, nb / 10, n, is_unsigned);
		ft_putchar_pf(output, nb % 10 + '0', n);
	}
}

void	ft_puthexa_pf(int output, unsigned long long int nb, int *n, int c)
{
	char	*base;

	if (c == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb <= 15)
		ft_putchar_pf(output, (base[0 + nb]), n);
	if (nb > 15)
	{
		ft_puthexa_pf(output, nb / 16, n, c);
		ft_putchar_pf(output, (base[0 + nb % 16]), n);
	}
}

void	ft_putptr_pf(int output, unsigned long int ptr, int *n)
{
	if (ptr == 0)
		return (ft_putstr_pf(output, "(nil)", n));
	ft_putstr_pf(output, "0x", n);
	ft_puthexa_pf(output, ptr, n, 0);
}
