
#include "minishell.h"
#include "minishell_louis.h"

int	bt_pwd(void)
{
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	return (1);
}