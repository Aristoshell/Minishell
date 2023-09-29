
#include "minishell.h"
#include "minishell_louis.h"

void	ft_set_flag(int *flag, char *val)
{
	*flag = MASK_EXPORT;
	if (val)
		*flag |= MASK_SET;
}
