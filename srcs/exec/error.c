
#include "minishell.h"
#include "minishell_louis.h"

void	error_dup2(void)
{
	printf("erno : %s\n", strerror(errno));
	exit(1);
}

void	error_pipe(void)
{
	printf("error pipe");
	exit(1);
}

void	error_fork(void)
{
	printf("error_fork");
	exit(1);
}

void	error_malloc(void)
{
	printf("error_malloc");
	exit(1);
}
