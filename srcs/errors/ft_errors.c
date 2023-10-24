
#include "minishell.h"
#include "minishell_louis.h"

int	ft_error(int err_code, char *arg)
{
	if (err_code == WRONG_NB_ARG)
		ft_dprintf(STDERR_FILENO, D_ER_ARG);
	else if (err_code == NO_ENV)
		ft_dprintf(STDERR_FILENO, D_ER_ENV);
	else if (err_code == MEMORY_ERR_NB)
		ft_dprintf(STDERR_FILENO, D_ER_MEM);
	else if (err_code == SYNTAX_QUOTE_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_SYN_QUOTE);
	else if (err_code == SYNTAX_PIPE_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_SYN_PIPE);
	else if (err_code == SYNTAX_NEWL_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_SYN_NL);
	else if (err_code == SYNTAX_FROM_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_SYN_FROM);
	else if (err_code == SYNTAX_HERED_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_SYN_HERED);
	else if (err_code == SYNTAX_TO_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_SYN_TO);
	else if (err_code == SYNTAX_APPND_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_SYN_APPEND);
	else if (err_code == PERM_DENIED_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_PERM, arg);
	else if (err_code == NO_FILEDIR_ERROR)
		ft_dprintf(STDERR_FILENO, D_ER_NO_FILDIR, arg);
	else if (err_code == WRONG_ID_EXPORT)
		ft_dprintf(STDERR_FILENO, D_ER_EXPAND, arg);
	else if (err_code == WRONG_CMD_ARG)
		ft_dprintf(STDERR_FILENO, D_ER_CMD_NF, arg);
	return (0);
}
