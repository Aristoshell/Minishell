
#include "minishell.h"
#include "minishell_louis.h"

void	swap(char ***tab, int i, int j)
{
	char	**temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

int compare(const char **a, const char **b)
{
	int	size_a;
	int	size_b;

	size_a = (int)ft_strlen(a[0]);
	size_b = (int)ft_strlen(b[0]);
	if (size_a < size_b)
		return (ft_strncmp(a[0], b[0], size_a));
	else
		return (ft_strncmp(a[0], b[0], size_b));
}

int	partition(char ***tab, int low, int high)
{
	char	**pivot;
	int		i;
	int		j;

	pivot = tab[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (compare((const char **)tab[j], (const char **)pivot) < 0)
		{
			i++;
			swap(tab, i, j);
		}
		j++;
	}
	swap(tab, i + 1, high);
	return (i + 1);
}

void	ft_quick_sort(char ***tab, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(tab, low, high);
		ft_quick_sort(tab, low, pivot - 1);
		ft_quick_sort(tab, pivot + 1, high);
	}
}
